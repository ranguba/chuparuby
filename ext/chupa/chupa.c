/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 *  Copyright (C) 2010  Kouhei Sutou <kou@clear-code.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */

#include <chupatext.h>
#include <ruby.h>

#ifndef CHUPA_BINDINGS_VERSION
#define CHUPA_BINDINGS_VERSION "0.0.0"
#endif

static void
quit_chupa(void *ptr)
{
    chupa_quit();
}

static VALUE
bindings_version(VALUE klass)
{
    return rb_str_new_cstr(CHUPA_BINDINGS_VERSION);
}

void
Init_chupa (void)
{
    int address;
    VALUE mChupa;

    chupa_init(&address);
    mChupa = rb_path2class("Chupa");
    rb_define_singleton_method(mChupa, "bindings_version", bindings_version, 0);
    rb_iv_set(mChupa, "quit", Data_Wrap_Struct(0, 0, quit_chupa, (void *)1));
}

/*
vi:ts=4:nowrap:ai:expandtab:sw=4
*/
