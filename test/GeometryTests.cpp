#include <QTest>

#include <GeometryPlugin/utils.h>

class UtilsTests : public QObject {
    Q_OBJECT
private slots:
    void testOrientations() {
        glm::vec2 a(0.0f, -1.0f);
        glm::vec2 b(0.0f,  0.0f);
        glm::vec2 c(0.5f,  1.0f);
        QVERIFY2(Point::getOrientation(a, b, c) == Orientation::CW, "Right Turn");

        a = { 0.0f, -1.0f};
        b = { 0.0f,  0.0f};
        c = {-0.5f,  1.0f};
        QVERIFY2(Point::getOrientation(a, b, c) == Orientation::CCW, "Left Turn");

        a = {0.0f, -1.0f};
        b = {0.0f,  0.0f};
        c = {0.0f,  1.0f};
        QVERIFY2(Point::getOrientation(a, b, c) == Orientation::COLLINEAR, "Collinear");
    }
};

int main(int argc, char *argv[])
{
    // setup lambda
    int status = 0;
    auto runTest = [&status, argc, argv](QObject* obj) {
        status |= QTest::qExec(obj, argc, argv);
    };

    // run suite
    runTest(new UtilsTests);
//    runTest(new AlgorithmTests);

    return status;
}

#include "GeometryTests.moc"
