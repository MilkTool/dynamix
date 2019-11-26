// DynaMix
// Copyright (c) 2013-2017 Borislav Stanimirov, Zahary Karadjov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

/**
 * \file
 * Common mutation rules classes.
 */

#include "config.hpp"
#include "mutation_rule.hpp"
#include "mixin_collection.hpp"

namespace dynamix
{

/**
 * A mutation rule for mutually exclusive mixins.
 *
 * If active, such rule will cause a mutation that adds one of the mutually
 * exclusive mixins, to remove all others.
 *
 * For example, if `a`, `b`, and `c` are mutually exclusive mixins,
 * any mutation that adds, say `a`, to an object, will automatically
 * remove `b` and `c` from it.
 */
class DYNAMIX_API mutually_exclusive_mixins : public mutation_rule, private mixin_collection
{
public:
    using mixin_collection::add;
    using mixin_collection::has;
    using mixin_collection::remove;

    /// Applies the rule to a mutation.
    virtual void apply_to(object_type_mutation& mutation) override;
};

/**
* A mutation rule for a bundle of mixins
*
* If active, such rule will cause a mutation that adds one of the bundled
* mixins, to add all others. And mutations that remove one of them, to
* remove all others, respectively.
*
* For example, if `a`, `b`, and `c` are bundled exclusive mixins,
* any mutation that adds, say `a`, to an object, will automatically
* add `b` and `c` to it. Respectively any mutation which removes, say,
* `c`, will also remove `a` and `b`.
*/
class DYNAMIX_API bundled_mixins : public mutation_rule, private mixin_collection
{
public:
    using mixin_collection::add;
    using mixin_collection::has;
    using mixin_collection::remove;

    /// Applies the rule to a mutation.
    virtual void apply_to(object_type_mutation& mutation) override;
};

/**
* A mutation rule for mixins dependent on another mixin
*
* If active such rule will cause any mutation that adds the master, to
* also add the dependencies. Mutations which remove the master will
* also remove the dependencies.
*
* The differnce between this and `bundled_mixins` is that only one mixin
* is used to determine whether the others are added or removed. Adding or
* removing any of the dependent mixins explicitly won't add or remove
* anything else.
*/
class DYNAMIX_API dependent_mixins : public mutation_rule, private mixin_collection
{
public:
    using mixin_collection::add;
    using mixin_collection::has;
    using mixin_collection::remove;

    /// Sets the master mixin. If it's added or removed in a mutation,
    /// all dependent mixins will also be added or removed from the object.
    template <typename Mixin>
    void set_master()
    {
        _master_id =_dynamix_get_mixin_type_info(static_cast<Mixin*>(nullptr)).id;
    }

    /// Applies the rule to a mutation.
    virtual void apply_to(object_type_mutation& mutation) override;

protected:
    mixin_id _master_id;
};

namespace internal
{
/// \internal
class DYNAMIX_API mandatory_mixin_impl : public mutation_rule
{
public:
    mandatory_mixin_impl(mixin_id id)
        : _id(id)
    {
    }

    virtual void apply_to(object_type_mutation& mutation) override;

protected:
    const mixin_id _id;
};

/// \internal
class DYNAMIX_API deprecated_mixin_impl : public mutation_rule
{
public:
    deprecated_mixin_impl(mixin_id id)
        : _id(id)
    {
    }

    virtual void apply_to(object_type_mutation& mutation) override;

protected:
    const mixin_id _id;
};

/// \internal
class DYNAMIX_API substitute_mixin_impl : public mutation_rule
{
public:
    substitute_mixin_impl(mixin_id src, mixin_id target)
        : _source_id(src)
        , _target_id(target)
    {
    }

    virtual void apply_to(object_type_mutation& mutation) override;

protected:
    const mixin_id _source_id;
    const mixin_id _target_id;
};
}

/**
 * A mutation rule for a mandatory mixin.
 *
 * If active, such rule will cause every mutation to always add the mixin
 * to an object and will ignore any attempts of a mutation to remove it.
 *
 * \tparam Mixin The mandatory mixin type
*/
template <typename Mixin>
class mandatory_mixin : public internal::mandatory_mixin_impl
{
public:
    mandatory_mixin()
        : mandatory_mixin_impl(_dynamix_get_mixin_type_info(static_cast<Mixin*>(nullptr)).id)
    {}
};

/**
 * A mutation rule for a deprecated mixin.
 *
 * If active, such rule will cause every mutation to always try to remove
 * the mixin from an object and will ignore any attempts of a mutation to
 * add it.
 *
 * \tparam Mixin The deprecated mixin type
*/
template <typename Mixin>
class deprecated_mixin : public internal::deprecated_mixin_impl
{
public:
    deprecated_mixin()
        : deprecated_mixin_impl(_dynamix_get_mixin_type_info(static_cast<Mixin*>(nullptr)).id)
    {}
};

/**
 * A mutation rule for a substitute mixin.
 *
 * If active, such rule will cause any mutation that tries to add
 * `SourceMixin` to instead add `TargetMixin`.
 *
 * \tparam SourceMixin The mixin type to be substituted
 * \tparam TargetMixin The mixin type that is the substitute
*/
template <typename SourceMixin, typename TargetMixin>
class substitute_mixin : public internal::substitute_mixin_impl
{
public:
    substitute_mixin()
        : substitute_mixin_impl(
            _dynamix_get_mixin_type_info(static_cast<SourceMixin*>(nullptr)).id,
            _dynamix_get_mixin_type_info(static_cast<TargetMixin*>(nullptr)).id)
    {}
};

} // namespace dynamix
