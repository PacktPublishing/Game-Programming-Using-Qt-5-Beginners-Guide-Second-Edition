#include <QString>
#include <QtTest>

class FirstTest : public QObject
{
  Q_OBJECT

public:
    FirstTest();

private Q_SLOTS:
    void testCase1();
    void firstTest() {
        //QFAIL("No way!");
        //QCOMPARE(1 + 1, 11);
    }
    void areMathematiciansCrazy() {
        if (1 != 2) {
            QSKIP("Thank goodness! 1 still isn't 2.");
        }
        //...
    }


    void test_data() {
        QTest::addColumn<QString>("string");
        QTest::addColumn<int>("count");
        QTest::newRow("simple string") << "Hello" << 5;
        QTest::newRow("with interpunctation") << "world!" << 6;
    }
    void test() {
        QFETCH(QString, string);
        QFETCH(int, count);
        QCOMPARE(string.count(), count);
    }
};

FirstTest::FirstTest()
{
}

void FirstTest::testCase1()
{
  QVERIFY2(true, "Failure");
}


QTEST_APPLESS_MAIN(FirstTest)

#include "tst_firsttest.moc"
