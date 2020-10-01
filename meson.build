# global project def
project('base_queue', 'c')

# ========= INSTALLATION CONTROL =========
# Install compiled libraries?
should_install_libs = false
if get_option('install_libs') == 'not_subproject'
    should_install_libs = not meson.is_subproject()
else
    should_install_libs = (get_option('install_libs') == 'yes')
endif

# Install headers?
should_install_headers = false
if get_option('install_headers') == 'not_subproject'
    should_install_headers = not meson.is_subproject()
else
    should_install_headers = (get_option('install_headers') == 'yes')
endif
# ========= END INSTALLATION CONTROL =========

# ========= BUILDING CONTROL =========
# Build tests?
should_build_tests = false
if get_option('build_tests') == 'yes'
    should_build_tests = true
elif get_option('build_tests') == 'not_subproject'
    should_build_tests = not meson.is_subproject()
endif
# ========= END BUILDING CONTROL =========

# ========= VERSION CONTROL INFO TAGGING ========
vcs_info = vcs_tag(
    command: ['git', 'rev-parse', 'HEAD'],
    input: 'templates/vcs_info.template.c',
    output: 'vcs_info.c',
    fallback: 'NOTFOUND'
)
# ========= END VERSION CONTROL INFO TAGGING ========


# ========= PROJECT VARIABLES =========
# Properties of the C compiler
cc = meson.get_compiler('c')

if get_option('buildtype') == 'debug'
    # enable alibc debug functions and debugging symbols.
    add_project_arguments('-DDEBUG=1',  '-ggdb3', language: 'c')
endif

# headers
includes    = include_directories('include')

# ========= END PROJECT VARIABLES =========

# ========= LIBRARY BUILD TARGETS =========

lib_queue = library(
    'libqueue', ['src/queue.c', vcs_info],
    include_directories: includes,
    link_with: [],
    install: should_install_libs
)
# ========= END LIBRARY BUILD TARGETS =========

# ========= DEPENDENCY OBJECTS FOR SUPERPROJECT BUILDS =========
dep_queue = declare_dependency(
    include_directories: includes,
    link_with: [lib_queue]
)
# ========= END DEPENDENCY OBJECTS FOR SUPERPROJECT BUILDS =========

# ========= UNIT TEST BUILD TARGETS =========
ext_cmocka       = dependency('cmocka', required: false)
if ext_cmocka.found() and should_build_tests
    exe_queue_test = executable(
        'test_queue', 'tests/test_queue.c',
        include_directories: includes,
        link_with: [lib_queue],
        dependencies: ext_cmocka
    )

    # test run targets
    test('test_queue', exe_queue_test)
endif
# ========= END UNIT TEST BUILD TARGETS =========

# ========= HEADER INSTALLATION CONFIG =========
if should_install_headers
    install_subdir(
        get_option('includedir'),
        strip_directory: true,
        install_dir: join_paths(get_option('prefix'), 'include')
    )
endif
