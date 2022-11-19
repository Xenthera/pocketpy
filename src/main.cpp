#include <fstream>

#include "pocketpy.h"

#define PK_DEBUG_TIME

struct Timer{
    const char* title;
    Timer(const char* title) : title(title) {}
    void run(std::function<void()> f){
        auto start = std::chrono::high_resolution_clock::now();
        f();
        auto end = std::chrono::high_resolution_clock::now();
        double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
#ifdef PK_DEBUG_TIME
        std::cout << title << ": " << elapsed << " s" << std::endl;
#endif
    }
};

#if defined(__EMSCRIPTEN__) || defined(__wasm__) || defined(__wasm32__) || defined(__wasm64__)

// these code is for demo use, feel free to modify it

REPL* _repl;

extern "C" {
    __EXPORT
    void repl_start(){
        VM* vm = pkpy_new_vm(true);
        _repl = pkpy_new_repl(vm, false);
    }

    __EXPORT
    bool repl_input(const char* line){
        return pkpy_repl_input(_repl, line);
    }
}

#else

int main(int argc, char** argv){
    if(argc == 1){
        VM* vm = pkpy_new_vm(true);
        // for(auto& kv : _strIntern)
        //     std::cout << kv.first << ", ";
        REPL repl(vm);
        while(true){
            std::string line;
            std::getline(std::cin, line);
            repl.input(line);
        }
        return 0;
    }
    
    if(argc == 2){
        std::string filename = argv[1];
        if(filename == "-h" || filename == "--help") goto __HELP;

        std::ifstream file(filename);
        if(!file.is_open()){
            std::cerr << "File not found: " << filename << std::endl;
            return 1;
        }
        std::string src((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        ThreadedVM* vm = pkpy_new_tvm(true);
        _Code code;
        Timer("Compile time").run([&]{
            code = compile(vm, src.c_str(), filename);
        });
        if(code == nullptr) return 1;
        //std::cout << code->toString() << std::endl;

        Timer("Running time").run([=]{
            vm->exec(code);
        });

        // Timer("Running time").run([=]{
        //     vm->startExec(code);
        //     while(pkpy_tvm_get_state(vm) != THREAD_FINISHED){
        //         if(pkpy_tvm_get_state(vm) == THREAD_SUSPENDED){
        //             std::string line;
        //             std::getline(std::cin, line);
        //             pkpy_tvm_write_stdin(vm, line.c_str());
        //             pkpy_tvm_resume(vm);
        //         }
        //     }
        // });
        return 0;
    }

__HELP:
    std::cout << "Usage: pocketpy [filename]" << std::endl;
    return 0;
}

#endif