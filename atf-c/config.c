/*
 * Automated Testing Framework (atf)
 *
 * Copyright (c) 2008, 2009 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND
 * CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdbool.h>
#include <string.h>

#include "atf-c/config.h"
#include "atf-c/env.h"
#include "atf-c/sanity.h"

static bool initialized = false;
static const char *atf_arch = NULL;
static const char *atf_build_cc = NULL;
static const char *atf_build_cflags = NULL;
static const char *atf_build_cpp = NULL;
static const char *atf_build_cppflags = NULL;
static const char *atf_build_cxx = NULL;
static const char *atf_build_cxxflags = NULL;
static const char *atf_confdir = NULL;
static const char *atf_libexecdir = NULL;
static const char *atf_machine = NULL;
static const char *atf_pkgdatadir = NULL;
static const char *atf_shell = NULL;
static const char *atf_workdir = NULL;

/* Only used for unit testing, so this prototype is private. */
void __atf_config_reinit(void);

/* ---------------------------------------------------------------------
 * Auxiliary functions.
 * --------------------------------------------------------------------- */

static
void
initialize_var(char const **valptr, const char *name, const char *def)
{
    PRE(*valptr == NULL);

    if (atf_env_has(name)) {
        const char *val = atf_env_get(name);
        if (strlen(val) > 0)
            *valptr = val;
        else
            *valptr = def;
    } else
        *valptr = def;

    POST(*valptr != NULL);
}

static
void
initialize(void)
{
    PRE(!initialized);

#define INITIALIZE_VAR(lc, uc) initialize_var(&lc, #uc, uc)
    INITIALIZE_VAR(atf_arch,           ATF_ARCH);
    INITIALIZE_VAR(atf_build_cc,       ATF_BUILD_CC);
    INITIALIZE_VAR(atf_build_cflags,   ATF_BUILD_CFLAGS);
    INITIALIZE_VAR(atf_build_cpp,      ATF_BUILD_CPP);
    INITIALIZE_VAR(atf_build_cppflags, ATF_BUILD_CPPFLAGS);
    INITIALIZE_VAR(atf_build_cxx,      ATF_BUILD_CXX);
    INITIALIZE_VAR(atf_build_cxxflags, ATF_BUILD_CXXFLAGS);
    INITIALIZE_VAR(atf_confdir,        ATF_CONFDIR);
    INITIALIZE_VAR(atf_libexecdir,     ATF_LIBEXECDIR);
    INITIALIZE_VAR(atf_machine,        ATF_MACHINE);
    INITIALIZE_VAR(atf_pkgdatadir,     ATF_PKGDATADIR);
    INITIALIZE_VAR(atf_shell,          ATF_SHELL);
    INITIALIZE_VAR(atf_workdir,        ATF_WORKDIR);
#undef INITIALIZE_VAR

    initialized = true;
}

/* ---------------------------------------------------------------------
 * Free functions.
 * --------------------------------------------------------------------- */

const char *
atf_config_get(const char *var)
{
    const char *value;

    if (!initialized) {
        initialize();
        INV(initialized);
    }

    if (strcmp(var, "atf_arch") == 0)
        value = atf_arch;
    else if (strcmp(var, "atf_build_cc") == 0)
        value = atf_build_cc;
    else if (strcmp(var, "atf_build_cflags") == 0)
        value = atf_build_cflags;
    else if (strcmp(var, "atf_build_cpp") == 0)
        value = atf_build_cpp;
    else if (strcmp(var, "atf_build_cppflags") == 0)
        value = atf_build_cppflags;
    else if (strcmp(var, "atf_build_cxx") == 0)
        value = atf_build_cxx;
    else if (strcmp(var, "atf_build_cxxflags") == 0)
        value = atf_build_cxxflags;
    else if (strcmp(var, "atf_confdir") == 0)
        value = atf_confdir;
    else if (strcmp(var, "atf_libexecdir") == 0)
        value = atf_libexecdir;
    else if (strcmp(var, "atf_machine") == 0)
        value = atf_machine;
    else if (strcmp(var, "atf_pkgdatadir") == 0)
        value = atf_pkgdatadir;
    else if (strcmp(var, "atf_shell") == 0)
        value = atf_shell;
    else if (strcmp(var, "atf_workdir") == 0)
        value = atf_workdir;
    else {
        UNREACHABLE;
        value = NULL;
    }

    return value;
}

void
__atf_config_reinit(void)
{
    initialized = false;
    atf_arch = NULL;
    atf_build_cc = NULL;
    atf_build_cflags = NULL;
    atf_build_cpp = NULL;
    atf_build_cppflags = NULL;
    atf_build_cxx = NULL;
    atf_build_cxxflags = NULL;
    atf_confdir = NULL;
    atf_libexecdir = NULL;
    atf_machine = NULL;
    atf_pkgdatadir = NULL;
    atf_shell = NULL;
    atf_workdir = NULL;
}
