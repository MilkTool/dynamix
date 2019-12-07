// DynaMix
// Copyright (c) 2013-2019 Borislav Stanimirov, Zahary Karadjov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "rendering_messages.hpp"
#include <dynamix/define_message.hpp>

DYNAMIX_DEFINE_MESSAGE(render_on_target);
DYNAMIX_DEFINE_MESSAGE(render_on_backbuffer);
DYNAMIX_DEFINE_MESSAGE(set_casts_shadows);

DYNAMIX_DEFINE_MESSAGE(opengl_specific);
DYNAMIX_DEFINE_MESSAGE(opengl_specific_multicast);
