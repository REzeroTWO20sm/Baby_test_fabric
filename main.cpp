#include "baby_test.cpp"

class MyTest : public AbstractTest {
public:
    void SetUp() override {
        std::cout << "SetUp for MyTest" << std::endl;
    }
    void Run() override {
        std::cout << "Run for MyTest" << std::endl;
    }
    void TearDown() override {
        std::cout << "TearDown for MyTest" << std::endl << std::endl;
    }
};

class AnotherTest : public AbstractTest {
public:
    void SetUp() override {
        std::cout << "SetUp for AnotherTest" << std::endl;
    }
    void Run() override {
        std::cout << "Run for AnotherTest" << std::endl;
    }
    void TearDown() override {
        std::cout << "TearDown for AnotherTest" << std::endl << std::endl;
    }
};

class SpecialTest : public AbstractTest {
public:
    void SetUp() override {
        std::cout << "SetUp for SpecialTest" << std::endl;
    }
    void Run() override {
        std::cout << "Run for SpecialTest" << std::endl;
    }
    void TearDown() override {
        std::cout << "TearDown for SpecialTest" << std::endl << std::endl;
    }
};

class ComplexTest : public AbstractTest {
public:
    void SetUp() override {
        std::cout << "SetUp for ComplexTest" << std::endl;
    }
    void Run() override {
        std::cout << "Run for ComplexTest" << std::endl;
    }
    void TearDown() override {
        std::cout << "TearDown for ComplexTest" << std::endl << std::endl;
    }
};

class SimpleTest : public AbstractTest {
public:
    void SetUp() override {
        std::cout << "SetUp for SimpleTest" << std::endl;
    }
    void Run() override {
        std::cout << "Run for SimpleTest" << std::endl;
    }
    void TearDown() override {
        std::cout << "TearDown for SimpleTest" << std::endl << std::endl;
    }
};

int main() {
    TestRegistry& registry = TestRegistry::Instance();

    MyTest* myTest = new MyTest();
    registry.RegisterTestClass("MyTest", myTest);

    AnotherTest* anotherTest = new AnotherTest();
    registry.RegisterTestClass("AnotherTest", anotherTest);

    SpecialTest* specialTest = new SpecialTest();
    registry.RegisterTestClass("SpecialTest", specialTest);

    ComplexTest* complexTest = new ComplexTest();
    registry.RegisterTestClass("ComplexTest", complexTest);

    SimpleTest* simpleTest = new SimpleTest();
    registry.RegisterTestClass("SimpleTest", simpleTest);

    //запуск отдельных тестов
    registry.RunTest("MyTest");
    registry.RunTest("AnotherTest");

    //вывод всех тестов
    std::cout << "All tests: " << std::endl;
    for (const auto& name : registry.ShowAllTests()) {
        std::cout << name << std::endl;
    }std::cout << std::endl;

    //вывод тестов содержащих Test
    std::cout << "Tests with 'Test':" << std::endl;
    for (const auto& name : registry.ShowTests(Substr("Test"))) {
        std::cout << name << std::endl;
    }std::cout << std::endl;

    //запуск тестов начинающихся с C
    registry.RunTests(FullMatch("ComplexTest"));
    registry.RunTests(FullMatch("SimpleTest"));

    registry.Clear();
}
