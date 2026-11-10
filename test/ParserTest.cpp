#include <QtTest/QtTest>
#include "../src/Parser.h"
#include "../src/language/LanguageRepository.h"

class ParserTest : public QObject {
    Q_OBJECT

private Q_SLOTS:
    void initTestCase();

    void triggerUsesDefaultTarget();
    void triggerWithTargetOverride();
    void triggerWithSourceAndTargetOverride();
    void triggerWithHyphenPair();
    void triggerIsCaseInsensitive();
    void triggerRequiresWordBoundary();
    void longTriggerWins();
    void legacyTargetSyntax();
    void legacyPairSyntax();
    void triggerAloneIsInvalid();
    void emptyTextAfterOverrideIsInvalid();

private:
    LanguageRepository repository;
    Parser parser;
};

void ParserTest::initTestCase() {
    repository.initialize();
    parser.setRepository(&repository);
    parser.setTriggerPhrases({QStringLiteral("tr"), QStringLiteral("transl"), QStringLiteral("translate")});
    parser.setDefaultTargetLanguage(German);
}

void ParserTest::triggerUsesDefaultTarget() {
    const TranslationQuery *query = parser.parse(QStringLiteral("tr hello"));
    QCOMPARE(query->getText(), QStringLiteral("hello"));
    QCOMPARE(query->getTargetAbbreviation(), QStringLiteral("de"));
    QVERIFY(query->getSourceAbbreviation().isEmpty());
    delete query;
}

void ParserTest::triggerWithTargetOverride() {
    const TranslationQuery *query = parser.parse(QStringLiteral("tr es hola"));
    QCOMPARE(query->getText(), QStringLiteral("hola"));
    QCOMPARE(query->getTargetAbbreviation(), QStringLiteral("es"));
    QVERIFY(query->getSourceAbbreviation().isEmpty());
    delete query;
}

void ParserTest::triggerWithSourceAndTargetOverride() {
    const TranslationQuery *query = parser.parse(QStringLiteral("tr en es hello"));
    QCOMPARE(query->getText(), QStringLiteral("hello"));
    QCOMPARE(query->getSourceAbbreviation(), QStringLiteral("en"));
    QCOMPARE(query->getTargetAbbreviation(), QStringLiteral("es"));
    delete query;
}

void ParserTest::triggerWithHyphenPair() {
    const TranslationQuery *query = parser.parse(QStringLiteral("tr en-de house"));
    QCOMPARE(query->getText(), QStringLiteral("house"));
    QCOMPARE(query->getSourceAbbreviation(), QStringLiteral("en"));
    QCOMPARE(query->getTargetAbbreviation(), QStringLiteral("de"));
    delete query;
}

void ParserTest::triggerIsCaseInsensitive() {
    const TranslationQuery *query = parser.parse(QStringLiteral("TR hello"));
    QCOMPARE(query->getText(), QStringLiteral("hello"));
    QCOMPARE(query->getTargetAbbreviation(), QStringLiteral("de"));
    delete query;
}

void ParserTest::triggerRequiresWordBoundary() {
    const TranslationQuery *query = parser.parse(QStringLiteral("translations hello"));
    QVERIFY(query->getText().isEmpty());
    QVERIFY(query->getTargetAbbreviation().isEmpty());
    delete query;
}

void ParserTest::longTriggerWins() {
    const TranslationQuery *query = parser.parse(QStringLiteral("translate hello"));
    QCOMPARE(query->getText(), QStringLiteral("hello"));
    QCOMPARE(query->getTargetAbbreviation(), QStringLiteral("de"));
    delete query;
}

void ParserTest::legacyTargetSyntax() {
    const TranslationQuery *query = parser.parse(QStringLiteral("de Haus"));
    QCOMPARE(query->getText(), QStringLiteral("Haus"));
    QCOMPARE(query->getTargetAbbreviation(), QStringLiteral("de"));
    delete query;
}

void ParserTest::legacyPairSyntax() {
    const TranslationQuery *query = parser.parse(QStringLiteral("en-de house"));
    QCOMPARE(query->getText(), QStringLiteral("house"));
    QCOMPARE(query->getSourceAbbreviation(), QStringLiteral("en"));
    QCOMPARE(query->getTargetAbbreviation(), QStringLiteral("de"));
    delete query;
}

void ParserTest::triggerAloneIsInvalid() {
    const TranslationQuery *query = parser.parse(QStringLiteral("tr"));
    QVERIFY(query->getText().isEmpty());
    QVERIFY(query->getTargetAbbreviation().isEmpty());
    delete query;
}

void ParserTest::emptyTextAfterOverrideIsInvalid() {
    const TranslationQuery *query = parser.parse(QStringLiteral("tr es"));
    QVERIFY(query->getText().isEmpty());
    QCOMPARE(query->getTargetAbbreviation(), QStringLiteral("es"));
    delete query;
}

QTEST_MAIN(ParserTest)

#include "ParserTest.moc"
