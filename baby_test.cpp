#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <unordered_map>

class AbstractTest {
public:
    virtual void SetUp() = 0;
    virtual void Run() = 0;
    virtual void TearDown() = 0;
};

class TestRegistry {
private:
    std::unordered_map<std::string, AbstractTest*> tests;
    TestRegistry() {}
    TestRegistry(const TestRegistry&) = delete;
    TestRegistry& operator=(const TestRegistry&) = delete;

public:
    static TestRegistry& Instance() {
        static TestRegistry instance;
        return instance;
    }

    void RegisterTestClass(const std::string& name, AbstractTest* test) {
        tests[name] = test;
    }

    AbstractTest* CreateTest(const std::string& name) {
        if (tests.find(name) == tests.end()) {
            throw std::out_of_range("Test not registered: " + name);
        }
        return tests[name];
    }

    void RunTest(const std::string& name) {
        try {
            AbstractTest* test = CreateTest(name);
            test->SetUp();
            test->Run();
        } catch (...) {
            if (tests.find(name) != tests.end()) {
                tests[name]->TearDown();
            }
            throw;
        }
        if (tests.find(name) != tests.end()) {
            tests[name]->TearDown();
        }
    }

    std::vector<std::string> ShowAllTests() {
        std::vector<std::string> names;
        for (const auto& pair : tests) {
            names.push_back(pair.first);
        }
        std::sort(names.begin(), names.end());
        return names;
    }

    template <typename Predicate>
    std::vector<std::string> ShowTests(Predicate predicate) {
        std::vector<std::string> names;
        for (const auto& pair : tests) {
            if (predicate(pair.first)) {
                names.push_back(pair.first);
            }
        }
        std::sort(names.begin(), names.end());
        return names;
    }

    template <typename Predicate>
    void RunTests(Predicate predicate) {
        std::vector<std::string> names = ShowTests(predicate);
        for (const auto& name : names) {
            RunTest(name);
        }
    }

    void Clear() {
        tests.clear();
    }
};

struct FullMatch {
    std::string pattern;

    FullMatch(const std::string& pattern) : pattern(pattern) {}

    bool operator()(const std::string& name) const {
        return name == pattern;
    }
};

struct Substr {
    std::string pattern;

    Substr(const std::string& pattern) : pattern(pattern) {}

    bool operator()(const std::string& name) const {
        return name.find(pattern) != std::string::npos;
    }
};