// DynaMix
// Copyright (c) 2013-2018 Borislav Stanimirov, Zahary Karadjov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "dynlib_A.hpp"
#include <dynamix/object.hpp>
#include <dynamix/mutate.hpp>
#include <dynamix/define_mixin.hpp>

using namespace dynamix;

DYNAMIX_DECLARE_MIXIN(mixin_b);

extern "C" DYNAMIX_SYMBOL_EXPORT void modify_object(object* o)
{
    mutate(o).add<mixin_b>();
}

extern "C" DYNAMIX_SYMBOL_EXPORT void release_object(object* o)
{
    mutate(o).remove<mixin_b>();
}

class mixin_b
{
public:
    int dl_a_multicast()
    {
        return 1001;
    }
};

DYNAMIX_DEFINE_MIXIN(mixin_b, dl_a_multicast_msg);
