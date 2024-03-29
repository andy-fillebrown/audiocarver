/*
    csoundCore.h:

    Copyright (C) 2011 John ffitch and Chris Wilson

    This file is part of Csound.

    The Csound Library is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    Csound is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with Csound; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
    02111-1307 USA
*/


/* global variables lock support */
struct global_var_lock_t;

struct opcode_weight_cache_entry_t;

struct  dag_node_t;

struct dag_cache_entry_t;
#define DAG_2_CACHE_SIZE (128)
#define OPCODE_WEIGHT_CACHE_SIZE (128)

struct instr_semantics_t;

