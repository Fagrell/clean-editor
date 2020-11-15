#include "test-runner.h"

#include <QTest>

namespace CleanEditor::Util {

TestRunner &TestRunner::instance()
{
    static TestRunner runner;
    return runner;
}

int TestRunner::execTests(int argc, char **argv)
{
    auto execTest = [argc, argv](QObject *test) { return QTest::qExec(test, argc, argv); };

    int status = 0;
    for (const auto test : tests_) {
        status |= execTest(test);
    }
    return status;
}

} //namespace CleanEditor::Util
