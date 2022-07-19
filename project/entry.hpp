//
// Created by liga on 7/1/2022.
//

#ifndef HOTWHEELS_CSGO_EXTERNAL_ENTRY_HPP
#define HOTWHEELS_CSGO_EXTERNAL_ENTRY_HPP

#include <iostream>

#define hinstance HINSTANCE
#define hmodule   HMODULE
#define handle    HANDLE
#define lpdword   LPDWORD

#define dll_main                      DllMain
#define create_thread( function )     CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE )function, 0, 0, 0 )
#define fnv                           fnv::hash
#define get_proc_address              GetProcAddress
#define get_module_handle             GetModuleHandle
#define set_window_long               SetWindowLongA
#define find_window                   FindWindowA
#define call_window_proc              CallWindowProc
#define free_library_and_exit_thread  FreeLibraryAndExitThread
#define close_handle                  CloseHandle
#define free_console                  FreeConsole
#define disable_thread_library_calls  DisableThreadLibraryCalls
#define win_api                       WINAPI
#define get_window_thread_process_id  GetWindowThreadProcessId
#define find_window                   FindWindowA
#define get_async_key_state           GetAsyncKeyState
#define set_console_title             SetConsoleTitle
#define sleep                         Sleep
#define peek_message                  PeekMessageA
#define translate_message             TranslateMessage
#define dispatch_message              DispatchMessageA
#define show_window                   ShowWindow
#define extend_frame_into_client_area DwmExtendFrameIntoClientArea
#define create_window_ex              CreateWindowEx
#define register_class_ex             RegisterClassEx
#define load_cursor                   LoadCursor
#define load_icon                     LoadIcon
#define def_window_proc               DefWindowProc
#define zero_memory                   ZeroMemory
#define get_folder_path               SHGetFolderPath
#define create_file                   CreateFile
#define get_console_mode              GetConsoleMode
#define set_console_mode              SetConsoleMode
#define get_std_handle                GetStdHandle
#define get_async_key_state           GetAsyncKeyState
#define get_foreground_window         GetForegroundWindow

#endif // HOTWHEELS_CSGO_EXTERNAL_ENTRY_HPP
