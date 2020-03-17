// DynaMix
// Copyright (c) 2013-2020 Borislav Stanimirov, Zahary Karadjov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "config.hpp"
#include "object_mutator.hpp"

namespace dynamix
{

/// An object type template. Internally it represents a prepared object type
/// information.
///
/// It makes the construction of objects from the same type (same mixins)
/// slightly faster, than using `mutate`.
class DYNAMIX_API object_type_template : private internal::object_mutator
{
public:
    object_type_template();

    using internal::object_mutator::add;
    // does the actual creation of the type template
    using internal::object_mutator::create;
    using internal::object_mutator::mutation;

    // hiding the parent function, not using it
    void apply_to(object& o) const;
};

} // namespace dynamix
