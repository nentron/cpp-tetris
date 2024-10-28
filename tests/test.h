#pragma once

#include <iostream>
#include <string>

namespace testrunner{
    class TestRunner{
    private:
        int count_errors = 0;
    public:
        template<class TestFunc>
        void RunTest(TestFunc func, const std::string& test_name){
            try {
                func();
                std::cerr << test_name << " OK" << std::endl;
            } catch (const std::exception& e){
                std::cerr << test_name << " failed due " << e.what() << std::endl;
                ++count_errors;
            } catch (...){
                ++count_errors;
                std::cerr << "Unidentified error cought" << std::endl;
            }
        }

        ~TestRunner(){
            std::cerr.flush();
            if (count_errors > 0){
                std::cerr << count_errors << " unit tests failed. Terminated" << std::endl;
                exit(1);
            }
        }
    };

    template<typename T>
    bool AssertEqual(const T& first, const T& second, const std::string text){
        if (first != second){
            std::cerr << text << std::endl;
            return false;
        }
        return true;
    }
}

#define RUN_TEST(tr, func) tr.RunTest(func, #func)
