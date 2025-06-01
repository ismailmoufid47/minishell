
- don't include hidden files in * by itself, eg.: ls *

- sort the * output

- don't expand when the heredoc delimiter, eg: << *, <<  $HOME


-  ls | exit << stop | grep "asd"
Minishell: read_line: Permission denied
AddressSanitizer:DEADLYSIGNAL
=================================================================
==20368==ERROR: AddressSanitizer: SEGV on unknown address 0x5dc3c3cb2b10 (pc 0x71ef1fdb8a16 bp 0x5dc3c3cb2b10 sp 0x7ffe934d6660 T0)
==20368==The signal is caused by a WRITE memory access.
Minishell: ls: command not found
    #0 0x71ef1fdb8a15 in bool __sanitizer::atomic_compare_exchange_strong<__sanitizer::atomic_uint8_t>(__sanitizer::atomic_uint8_t volatile*, __sanitizer::atomic_uint8_t::Type*, __sanitizer::atomic_uint8_t::Type, __sanitizer::memory_order) ../../../../src/libsanitizer/sanitizer_common/sanitizer_atomic_clang.h:79
    #1 0x71ef1fdb8a15 in __asan::Allocator::AtomicallySetQuarantineFlagIfAllocated(__asan::AsanChunk*, void*, __sanitizer::BufferedStackTrace*) ../../../../src/libsanitizer/asan/asan_allocator.cc:552
    #2 0x71ef1fdb8a15 in __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType) ../../../../src/libsanitizer/asan/asan_allocator.cc:629
    #3 0x71ef1fdb8a15 in __asan::asan_free(void*, __sanitizer::BufferedStackTrace*, __asan::AllocType) ../../../../src/libsanitizer/asan/asan_allocator.cc:865
    #4 0x71ef1fe9d3d8 in __interceptor_free ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:127
    #5 0x5dc3c3cafbf7 in error utils/errors.c:7
    #6 0x5dc3c3cafb09 in open_wrapper utils/wrappers.c:19
    #7 0x5dc3c3cabff0 in handle_here_doc 4_execution/execute_utils.c:11
    #8 0x5dc3c3caa98c in redirect 4_execution/execute.c:23
    #9 0x5dc3c3cac653 in redirect_builtins builtins/builtins.c:12
    #10 0x5dc3c3cad4ef in exit_cmd builtins/builtins.c:137
    #11 0x5dc3c3cab83b in execute 4_execution/execute.c:132
    #12 0x5dc3c3cb0bd1 in main /workspaces/minishell/mandatory/shell.c:106
    #13 0x71ef1fb19082 in __libc_start_main ../csu/libc-start.c:308
    #14 0x5dc3c3ca56ed in _start (/workspaces/minishell/minishell+0x46ed)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV ../../../../src/libsanitizer/sanitizer_common/sanitizer_atomic_clang.h:79 in bool __sanitizer::atomic_compare_exchange_strong<__sanitizer::atomic_uint8_t>(__sanitizer::atomic_uint8_t volatile*, __sanitizer::atomic_uint8_t::Type*, __sanitizer::atomic_uint8_t::Type, __sanitizer::memory_order)
==20368==ABORTING
=================================================================
==101433==ERROR: AddressSanitizer: SEGV on unknown address 0x5fb981b2eab0 (pc 0x760f5b6ffa16 bp 0x5fb981b2eab0 sp 0x7ffc1377d010 T0)
==101433==The signal is caused by a WRITE memory access.






mwa7



=================================================================
==101430==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 44 byte(s) in 19 object(s) allocated from:
    #0 0x760f5b7e4c3e in __interceptor_realloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:163
    #1 0x760f5b54b297 in __GI___getcwd ../sysdeps/unix/sysv/linux/getcwd.c:84

Direct leak of 32 byte(s) in 8 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2d539 in ft_itoa (/workspaces/Mini-Shell/minishell+0x10539)
    #2 0x5fb981b27d98 in execute 4_execution/execute.c:171
    #3 0x5fb981b2cb0b in main /workspaces/Mini-Shell/mandatory/shell.c:106
    #4 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

Direct leak of 23 byte(s) in 1 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2cdc8 in ft_strdup (/workspaces/Mini-Shell/minishell+0xfdc8)
    #2 0x5fb981b2b04b in create_envp_node utils/envp_handler.c:51
    #3 0x5fb981b2b15c in set_envp utils/envp_handler.c:68
    #4 0x5fb981b2c72e in main /workspaces/Mini-Shell/mandatory/shell.c:67
    #5 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

Direct leak of 4 byte(s) in 2 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2d539 in ft_itoa (/workspaces/Mini-Shell/minishell+0x10539)
    #2 0x5fb981b27cdd in execute 4_execution/execute.c:167
    #3 0x5fb981b2cb0b in main /workspaces/Mini-Shell/mandatory/shell.c:106
    #4 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

Direct leak of 2 byte(s) in 1 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2cdc8 in ft_strdup (/workspaces/Mini-Shell/minishell+0xfdc8)
    #2 0x5fb981b28dd9 in cd builtins/builtins.c:88
    #3 0x5fb981b274ed in execute 4_execution/execute.c:126
    #4 0x5fb981b2cb0b in main /workspaces/Mini-Shell/mandatory/shell.c:106
    #5 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

SUMMARY: AddressSanitizer: 105 byte(s) leaked in 31 allocation(s).
    #0 0x760f5b6ffa15 in bool __sanitizer::atomic_compare_exchange_strong<__sanitizer::atomic_uint8_t>(__sanitizer::atomic_uint8_t volatile*, __sanitizer::atomic_uint8_t::Type*, __sanitizer::atomic_uint8_t::Type, __sanitizer::memory_order) ../../../../src/libsanitizer/sanitizer_common/sanitizer_atomic_clang.h:79
    #1 0x760f5b6ffa15 in __asan::Allocator::AtomicallySetQuarantineFlagIfAllocated(__asan::AsanChunk*, void*, __sanitizer::BufferedStackTrace*) ../../../../src/libsanitizer/asan/asan_allocator.cc:552
    #2 0x760f5b6ffa15 in __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType) ../../../../src/libsanitizer/asan/asan_allocator.cc:629
    #3 0x760f5b6ffa15 in __asan::asan_free(void*, __sanitizer::BufferedStackTrace*, __asan::AllocType) ../../../../src/libsanitizer/asan/asan_allocator.cc:865
    #4 0x760f5b7e43d8 in __interceptor_free ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:127
    #5 0x5fb981b2bb31 in error utils/errors.c:7
    #6 0x5fb981b2ba43 in open_wrapper utils/wrappers.c:19
    #7 0x5fb981b27f3e in handle_here_doc 4_execution/execute_utils.c:12
    #8 0x5fb981b268ce in redirect 4_execution/execute.c:23
    #9 0x5fb981b270c6 in execute_cmd 4_execution/execute.c:94
    #10 0x5fb981b2786f in execute 4_execution/execute.c:138
    #11 0x5fb981b2cb0b in main /workspaces/Mini-Shell/mandatory/shell.c:106
    #12 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308
    #13 0x5fb981b216ed in _start (/workspaces/Mini-Shell/minishell+0x46ed)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV ../../../../src/libsanitizer/sanitizer_common/sanitizer_atomic_clang.h:79 in bool __sanitizer::atomic_compare_exchange_strong<__sanitizer::atomic_uint8_t>(__sanitizer::atomic_uint8_t volatile*, __sanitizer::atomic_uint8_t::Type*, __sanitizer::atomic_uint8_t::Type, __sanitizer::memory_order)
==101433==ABORTING

=================================================================
==101431==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 44 byte(s) in 19 object(s) allocated from:
    #0 0x760f5b7e4c3e in __interceptor_realloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:163
    #1 0x760f5b54b297 in __GI___getcwd ../sysdeps/unix/sysv/linux/getcwd.c:84

Direct leak of 32 byte(s) in 8 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2d539 in ft_itoa (/workspaces/Mini-Shell/minishell+0x10539)
    #2 0x5fb981b27d98 in execute 4_execution/execute.c:171
    #3 0x5fb981b2cb0b in main /workspaces/Mini-Shell/mandatory/shell.c:106
    #4 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

Direct leak of 23 byte(s) in 1 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2cdc8 in ft_strdup (/workspaces/Mini-Shell/minishell+0xfdc8)
    #2 0x5fb981b2b04b in create_envp_node utils/envp_handler.c:51
    #3 0x5fb981b2b15c in set_envp utils/envp_handler.c:68
    #4 0x5fb981b2c72e in main /workspaces/Mini-Shell/mandatory/shell.c:67
    #5 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

Direct leak of 4 byte(s) in 2 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2d539 in ft_itoa (/workspaces/Mini-Shell/minishell+0x10539)
    #2 0x5fb981b27cdd in execute 4_execution/execute.c:167
    #3 0x5fb981b2cb0b in main /workspaces/Mini-Shell/mandatory/shell.c:106
    #4 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

Direct leak of 2 byte(s) in 1 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2cdc8 in ft_strdup (/workspaces/Mini-Shell/minishell+0xfdc8)
    #2 0x5fb981b28dd9 in cd builtins/builtins.c:88
    #3 0x5fb981b274ed in execute 4_execution/execute.c:126
    #4 0x5fb981b2cb0b in main /workspaces/Mini-Shell/mandatory/shell.c:106
    #5 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

SUMMARY: AddressSanitizer: 105 byte(s) leaked in 31 allocation(s).
codespace@codespaces-e140d8: /$ $USER
Minishell: codespace: command not found

=================================================================
==101449==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 44 byte(s) in 19 object(s) allocated from:
    #0 0x760f5b7e4c3e in __interceptor_realloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:163
    #1 0x760f5b54b297 in __GI___getcwd ../sysdeps/unix/sysv/linux/getcwd.c:84

Direct leak of 32 byte(s) in 8 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2d539 in ft_itoa (/workspaces/Mini-Shell/minishell+0x10539)
    #2 0x5fb981b27d98 in execute 4_execution/execute.c:171
    #3 0x5fb981b2cb0b in main /workspaces/Mini-Shell/mandatory/shell.c:106
    #4 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

Direct leak of 23 byte(s) in 1 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2cdc8 in ft_strdup (/workspaces/Mini-Shell/minishell+0xfdc8)
    #2 0x5fb981b2b04b in create_envp_node utils/envp_handler.c:51
    #3 0x5fb981b2b15c in set_envp utils/envp_handler.c:68
    #4 0x5fb981b2c72e in main /workspaces/Mini-Shell/mandatory/shell.c:67
    #5 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

Direct leak of 4 byte(s) in 2 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2d539 in ft_itoa (/workspaces/Mini-Shell/minishell+0x10539)
    #2 0x5fb981b27cdd in execute 4_execution/execute.c:167
    #3 0x5fb981b2cb0b in main /workspaces/Mini-Shell/mandatory/shell.c:106
    #4 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

Direct leak of 2 byte(s) in 1 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2cdc8 in ft_strdup (/workspaces/Mini-Shell/minishell+0xfdc8)
    #2 0x5fb981b28dd9 in cd builtins/builtins.c:88
    #3 0x5fb981b274ed in execute 4_execution/execute.c:126
    #4 0x5fb981b2cb0b in main /workspaces/Mini-Shell/mandatory/shell.c:106
    #5 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

SUMMARY: AddressSanitizer: 105 byte(s) leaked in 31 allocation(s).
codespace@codespaces-e140d8: /$ asd
Minishell: asd: command not found

=================================================================
==101453==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 44 byte(s) in 19 object(s) allocated from:
    #0 0x760f5b7e4c3e in __interceptor_realloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:163
    #1 0x760f5b54b297 in __GI___getcwd ../sysdeps/unix/sysv/linux/getcwd.c:84

Direct leak of 32 byte(s) in 8 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2d539 in ft_itoa (/workspaces/Mini-Shell/minishell+0x10539)
    #2 0x5fb981b27d98 in execute 4_execution/execute.c:171
    #3 0x5fb981b2cb0b in main /workspaces/Mini-Shell/mandatory/shell.c:106
    #4 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

Direct leak of 23 byte(s) in 1 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2cdc8 in ft_strdup (/workspaces/Mini-Shell/minishell+0xfdc8)
    #2 0x5fb981b2b04b in create_envp_node utils/envp_handler.c:51
    #3 0x5fb981b2b15c in set_envp utils/envp_handler.c:68
    #4 0x5fb981b2c72e in main /workspaces/Mini-Shell/mandatory/shell.c:67
    #5 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

Direct leak of 4 byte(s) in 2 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2d539 in ft_itoa (/workspaces/Mini-Shell/minishell+0x10539)
    #2 0x5fb981b27cdd in execute 4_execution/execute.c:167
    #3 0x5fb981b2cb0b in main /workspaces/Mini-Shell/mandatory/shell.c:106
    #4 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

Direct leak of 2 byte(s) in 1 object(s) allocated from:
    #0 0x760f5b7e4808 in __interceptor_malloc ../../../../src/libsanitizer/asan/asan_malloc_linux.cc:144
    #1 0x5fb981b2cdc8 in ft_strdup (/workspaces/Mini-Shell/minishell+0xfdc8)
    #2 0x5fb981b28dd9 in cd builtins/builtins.c:88
    #3 0x5fb981b274ed in execute 4_execution/execute.c:126
    #4 0x5fb981b2cb0b in main /workspaces/Mini-Shell/mandatory/shell.c:106
    #5 0x760f5b460082 in __libc_start_main ../csu/libc-start.c:308

SUMMARY: AddressSanitizer: 105 byte(s) leaked in 31 allocation(s).
codespace@codespaces-e140d8: /$ /bin/rm -f out
codespace@codespaces-e140d8: /$ 
codespace@codespaces-e140d8: /$ ls|cat Makefile|cat<<'asd'>out
Minishell: ls: command not found
Minishell: cat: command not found
Minishell: read_line: Permission denied
AddressSanitizer:DEADLYSIGNAL
=================================================================
==101462==ERROR: AddressSanitizer: SEGV on unknown address 0x5fb981b2eab0 (pc 0x760f5b6ffa16 bp 0x5fb981b2eab0 sp 0x7ffc1377d010 T0)
==101462==The signal is caused by a WRITE memory access.