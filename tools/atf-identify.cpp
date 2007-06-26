//
// Automated Testing Framework (atf)
//
// Copyright (c) 2007 The NetBSD Foundation, Inc.
// All rights reserved.
//
// This code is derived from software contributed to The NetBSD Foundation
// by Julio M. Merino Vidal, developed as part of Google's Summer of Code
// 2007 program.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
// 3. All advertising materials mentioning features or use of this
//    software must display the following acknowledgement:
//        This product includes software developed by the NetBSD
//        Foundation, Inc. and its contributors.
// 4. Neither the name of The NetBSD Foundation nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND
// CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
// INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
// IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
// IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#include <cstdlib>
#include <iostream>
#include <string>

#include "libatf.hpp"

#include "libatfmain/atffile.hpp"
#include "libatfmain/application.hpp"
#include "libatfmain/filesystem.hpp"

namespace am = atf::main;

std::string
identify(const std::string& name, const std::string& curdir)
{
    assert(curdir[curdir.length() - 1] == '/');

    am::directory dir(curdir);
    if (!dir.has(name))
        throw atf::not_found_error< std::string >
            ("Cannot locate test program", name);

    std::string ident;

    am::atffile af(curdir + "Atffile");
    if (!af.has(name))
        throw atf::not_found_error< std::string >
            ("The test program is not listed in the Atffile", name);

    std::string base = am::get_leaf_name(curdir);
    std::string d = am::get_branch_path(curdir);
    try {
        ident = identify(base, d + "/");
    } catch (const atf::not_found_error< std::string >&e ) {
        // Do nothing.
    }
    ident += "/" + name;

    return ident;
}

class atf_identify : public am::application {
    std::string specific_args(void) const;

public:
    int main(void);
};

std::string
atf_identify::specific_args(void)
    const
{
    return "<test-program>";
}

int
atf_identify::main(void)
{
    if (m_argc < 1)
        throw am::usage_error("No test program specified");

    int errcode;
    std::string tp(m_argv[0]);

    try {
        std::string ident = identify(tp, am::get_work_dir() + "/");
        std::cout << ident << std::endl;
        errcode = EXIT_SUCCESS;
    } catch (const atf::not_found_error< std::string >& e) {
        std::cerr << "Cannot calculate identifier for " << tp
                  << ": " << e.what() << std::endl;
        errcode = EXIT_FAILURE;
    }

    return errcode;
}

int
main(int argc, char* const* argv)
{
    return atf_identify().run(argc, argv);
}
