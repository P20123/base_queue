# base\_queue

Simple character queue in C, with no `stdlib` or dynamic memory requirements.

This says everything you'll need to know:
```
------------------------------------------------------------------------------
                           GCC Code Coverage Report
Directory: /home/andy/workspace/k64_firmware/subprojects/base_queue
------------------------------------------------------------------------------
File                                       Lines    Exec  Cover   Missing
------------------------------------------------------------------------------
src/queue.c                                   36      36   100%   
tests/test_queue.c                            49      49   100%   
------------------------------------------------------------------------------
TOTAL                                         85      85   100%
------------------------------------------------------------------------------
```

## Building
Standard Meson build process.  Tests require `cmocka`.
Enable testing with:
	`meson configure -Dbuild_tests=true`.

Coverage requires `gcovr`.
Enable coverage with:
	`meson configure -Db_coverage=true`
