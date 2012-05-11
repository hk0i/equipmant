#include "GScriptHighlighter.h"

GScriptHighlighter::GScriptHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightRule rule;

    //keyword formatting
    m_keyword_format.setFontWeight(QFont::Bold);
    m_keyword_format.setForeground(QColor("#3465A4"));

    QStringList keywords;
    keywords << "\\binput\\b"
        << "\\bpause\\b"
        << "\\bMain\\b"
        << "\\bSub\\b"
        << "\\bRange\\b"
        << "\\bAmmo\\b"

        << "\\bHead\\b"
        << "\\bNeck\\b"
        << "\\bL.Ear\\b"
        << "\\bR.Ear\\b"

        << "\\bBody\\b"
        << "\\bHands\\b"
        << "\\bL.Ring\\b"
        << "\\bR.Ring\\b"

        << "\\bBack\\b"
        << "\\bWaist\\b"
        << "\\bLegs\\b"
        << "\\bFeet\\b";

    foreach(const QString &pattern, keywords) {
        rule.pattern = QRegExp(pattern);
        rule.format = m_keyword_format;
        m_highlight_rules << rule;
    }

    //quoted string formatting
    m_quote_format.setForeground(QColor("#A40000"));
    rule.pattern = QRegExp("\"[^\"]+\"");
    rule.format = m_quote_format;
    m_highlight_rules << rule;

    //comment formatting
    m_comment_format.setForeground(QColor("#4E9A06"));
    m_comment_format.setFontItalic(true);
    rule.pattern = QRegExp("//[^\n]*$");
    rule.format = m_comment_format;
    m_highlight_rules << rule;

    //target formatting
    m_target_format.setFontWeight(QFont::Bold);
    rule.pattern = QRegExp("<[^>]+>");
    rule.format = m_target_format;
    m_highlight_rules << rule;

    //number formatting
    m_number_format.setFontWeight(QFont::Bold);
    m_number_format.setForeground(QColor("#CE5C00"));
    rule.pattern = QRegExp("\\b\\d+\\b");
    rule.format = m_number_format;
    m_highlight_rules << rule;
}

void GScriptHighlighter::highlightBlock(const QString &text)
{
    foreach(const HighlightRule &rule, m_highlight_rules) {
        QRegExp re(rule.pattern);
        int index = re.indexIn(text);
        while (index >= 0) {
            int length = re.matchedLength();
            setFormat(index, length, rule.format);
            index = re.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);
}
