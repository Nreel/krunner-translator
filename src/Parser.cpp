//
// Created by David Baum on 23.09.20.
//

#include "Parser.h"

void Parser::setRepository(LanguageRepository *newRepository) {
    repository = newRepository;
}

void Parser::setTriggerPhrases(const QStringList &phrases) {
    triggerPhrases = phrases;
}

void Parser::setDefaultTargetLanguage(SupportedLanguage language) {
    defaultTargetLanguage = language;
}

QString Parser::matchedTrigger(const QString &term) const {
    QString match;
    for (const QString &rawPhrase : triggerPhrases) {
        const QString phrase = rawPhrase.trimmed();
        if (phrase.isEmpty() || phrase.size() > term.size()) continue;
        if (term.left(phrase.size()).compare(phrase, Qt::CaseInsensitive) != 0) continue;
        if (term.size() != phrase.size() && !term.at(phrase.size()).isSpace()) continue;
        if (phrase.size() > match.size()) {
            match = phrase;
        }
    }
    return match;
}

TranslationQuery* Parser::parse(const QString &term) {
    TranslationQuery *query = new TranslationQuery(repository);
    QString remainder = term.trimmed();
    if (remainder.isEmpty()) return query;

    const QString trigger = matchedTrigger(remainder);
    const bool hasTrigger = !trigger.isEmpty();
    if (hasTrigger) {
        remainder = remainder.mid(trigger.size()).trimmed();
        if (remainder.isEmpty()) return query;
        query->setTargetLanguage(defaultTargetLanguage);
    }

    const QStringList tokens = remainder.split(QLatin1Char(' '), Qt::SkipEmptyParts);
    if (tokens.isEmpty()) return query;

    const QString firstToken = tokens.first();
    const int separatorIndex = firstToken.indexOf(separator);
    int textStart = 0;

    if (separatorIndex > 0) {
        const SupportedLanguage sourceLanguage =
                repository->getSupportedLanguage(firstToken.left(separatorIndex));
        const SupportedLanguage targetLanguage =
                repository->getSupportedLanguage(firstToken.mid(separatorIndex + 1));
        if (sourceLanguage != INVALID && targetLanguage != INVALID) {
            query->setSourceLanguage(sourceLanguage);
            query->setTargetLanguage(targetLanguage);
            textStart = 1;
        } else if (!hasTrigger) {
            return query;
        }
    } else if (repository->containsAbbreviation(firstToken)) {
        if (tokens.size() >= 2 && repository->containsAbbreviation(tokens.at(1))) {
            query->setSourceLanguage(repository->getSupportedLanguage(firstToken));
            query->setTargetLanguage(repository->getSupportedLanguage(tokens.at(1)));
            textStart = 2;
        } else {
            query->setTargetLanguage(repository->getSupportedLanguage(firstToken));
            textStart = 1;
        }
    } else if (!hasTrigger) {
        // Without a trigger the first token must be a language code; otherwise
        // the query is not meant for this runner.
        return query;
    }

    query->setText(tokens.mid(textStart).join(QLatin1Char(' ')));
    return query;
}
