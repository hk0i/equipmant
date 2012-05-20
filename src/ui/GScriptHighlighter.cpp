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
        << "\\bexec\\b"
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

    //quoted string formatting
    m_quote_format.setForeground(QColor("#A40000"));
    rule.pattern = QRegExp("\"[^\"]+\"");
    rule.format = m_quote_format;
    m_highlight_rules << rule;

    //exec arg formatting
    //qt4 regex does not support lookbehinds, so this will paint it red
    //and the foreach below will paint the exec blue
    rule.pattern = QRegExp("exec [^\n]*$");
    rule.format = m_quote_format;
    m_highlight_rules << rule;

    foreach(const QString &pattern, keywords) {
        rule.pattern = QRegExp(pattern);
        rule.format = m_keyword_format;
        m_highlight_rules << rule;
    }




    //target formatting
    m_target_format.setFontWeight(QFont::Bold);
    rule.pattern = QRegExp("<(t|bt|me|st|stpc|stnpc|stpt)>");
    rule.format = m_target_format;
    m_highlight_rules << rule;

    //number formatting
    m_number_format.setFontWeight(QFont::Bold);
    m_number_format.setForeground(QColor("#CE5C00"));
    rule.pattern = QRegExp("\\b\\d+\\b");
    rule.format = m_number_format;
    m_highlight_rules << rule;

    //party chat formatting
    m_party_format.setForeground(QColor("#3465A4"));
    rule.pattern = QRegExp("/(p|party)\\b .*$");
    rule.format = m_party_format;
    m_highlight_rules << rule;

    //party chat formatting
    m_linkshell_format.setForeground(QColor("#4E9A06"));
    rule.pattern = QRegExp("/(l|linkshell)\\b .*$");
    rule.format = m_linkshell_format;
    m_highlight_rules << rule;

    //echo chat formatting
    m_echo_format.setForeground(QColor("#c4a000"));
    rule.pattern = QRegExp("(/echo)\\b .*$");
    rule.format = m_echo_format;
    m_highlight_rules << rule;

    //comment formatting
    m_comment_format.setForeground(QColor("#4E9A06"));
    m_comment_format.setFontItalic(true);
    rule.pattern = QRegExp("//[^\n]*$");
    rule.format = m_comment_format;
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
