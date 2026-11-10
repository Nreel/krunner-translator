//
// Created by David Baum on 23.09.20.
//

#ifndef RUNNERTRANSLATOR_PARSER_H
#define RUNNERTRANSLATOR_PARSER_H


#include <QtCore/QString>
#include <QtCore/QStringList>
#include <src/language/Language.h>
#include <src/language/LanguageRepository.h>
#include "TranslationQuery.h"

class Parser {
public:
    void setRepository(LanguageRepository * repository);
    void setTriggerPhrases(const QStringList &phrases);
    void setDefaultTargetLanguage(SupportedLanguage language);
    TranslationQuery* parse(const QString &term);

private:
    QString matchedTrigger(const QString &term) const;

    LanguageRepository * repository = nullptr;
    QStringList triggerPhrases;
    SupportedLanguage defaultTargetLanguage = INVALID;
    const QString separator = QStringLiteral("-");
};

#endif //RUNNERTRANSLATOR_PARSER_H
