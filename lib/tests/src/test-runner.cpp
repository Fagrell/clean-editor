#include "test-runner.h"

#include <QTest>
#include <algorithm>

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
    std::for_each(begin(tests_), end(tests_), [&status, &execTest](const auto &test) {
        status |= execTest(test);
    });
    return status;
}

} //namespace CleanEditor::Util
