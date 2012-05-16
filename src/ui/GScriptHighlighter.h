#ifndef GSCRIPTHIGHLIGHTER_H
#define GSCRIPTHIGHLIGHTER_H

#include <QSyntaxHighlighter>

#include <QHash>
#include <QTextCharFormat>
#include "Equip.h"

class GScriptHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

    public:
        GScriptHighlighter(QTextDocument *parent);

    protected:
        void highlightBlock(const QString &text);

    private:
        struct HighlightRule
        {
            QRegExp pattern;
            QTextCharFormat format;
        };

        QVector<HighlightRule> m_highlight_rules;

        QRegExp m_comment_start_expression;

        QTextCharFormat m_keyword_format;
        QTextCharFormat m_comment_format;
        QTextCharFormat m_quote_format;
        QTextCharFormat m_target_format;
        QTextCharFormat m_number_format;

        //chat syntax highlighting rules
        QTextCharFormat m_party_format;
        QTextCharFormat m_linkshell_format;
        QTextCharFormat m_echo_format;


};


#endif
