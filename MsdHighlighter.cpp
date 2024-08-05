/****************************************************************************
 ** Deling Final Fantasy VIII Field Editor
 ** Copyright (C) 2009-2012 Arzel Jérôme <myst6re@gmail.com>
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#include "MsdHighlighter.h"

MsdHighlighter::MsdHighlighter(QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
	HighlightingRule rule;

	rule.pattern = QRegularExpression("\1");
	rule.color = Qt::darkRed;
	highlightingRules.append(rule);

	QStringList names;
	names << "\\{Squall\\}" << "\\{Zell\\}" << "\\{Irvine\\}" << "\\{Quistis\\}" << "\\{Rinoa\\}"
		  << "\\{Selphie\\}" << "\\{Seifer\\}" << "\\{Edea\\}" << "\\{Laguna\\}" << "\\{Kiros\\}"
		  << "\\{Ward\\}" << "\\{Angelo\\}" << "\\{Griever\\}" << "\\{Boko\\}"
		  << "\\{Galbadia\\}" << "\\{Esthar\\}" << "\\{Balamb\\}" << "\\{Dollet\\}"
		  << "\\{Timber\\}" << "\\{Trabia\\}" << "\\{Centra\\}" << "\\{Horizon\\}";

	foreach(const QString &name, names) {
		rule.pattern = QRegularExpression(name);
		rule.color = Qt::darkGreen;
		highlightingRules.append(rule);
	}

	QStringList syst;
	syst << "\\{Darkgrey\\}" << "\\{Grey\\}" << "\\{Yellow\\}" << "\\{Red\\}"
		  << "\\{Green\\}" << "\\{Blue\\}" << "\\{Purple\\}" << "\\{White\\}"
		  << "\\{DarkgreyBlink\\}" << "\\{GreyBlink\\}" << "\\{YellowBlink\\}"
		  << "\\{RedBlink\\}" << "\\{GreenBlink\\}" << "\\{BlueBlink\\}"
		  << "\\{PurpleBlink\\}" << "\\{WhiteBlink\\}" << "\\{Wait\\d\\d\\d\\}"
		  << "\\{Var[0b]?[0-7]\\}" << "^\\{NewPage\\}$" << "\\{jp\\d\\d\\d\\}";
  
  for (const QString &s : syst) {
      rule.pattern = QRegularExpression(s, QRegularExpression::CaseInsensitiveOption);
      rule.color = Qt::darkBlue;
      highlightingRules.append(rule);
  }

	QStringList doublet;
	doublet << "\\{in\\}" << "\\{e \\}" << "\\{ne\\}" << "\\{to\\}" << "\\{re\\}" << "\\{HP\\}" << "\\{l \\}" << "\\{ll\\}" <<
			"\\{GF\\}" << "\\{nt\\}" << "\\{il\\}" << "\\{o \\}" << "\\{ef\\}" << "\\{on\\}" << "\\{ w\\}" << "\\{ r\\}" <<
			"\\{wi\\}" << "\\{fi\\}" << "\\{EC\\}" << "\\{s \\}" << "\\{ar\\}" << "\\{FE\\}" << "\\{ S\\}" << "\\{ag\\}";

	foreach(const QString &d, doublet) {
		rule.pattern = QRegularExpression(d);
		rule.color = Qt::darkBlue;
		highlightingRules.append(rule);
	}
}

void MsdHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : highlightingRules) {
        QRegularExpression expression(rule.pattern);
        QRegularExpressionMatch match = expression.match(text);
        int index = match.capturedStart();
        
        while (match.hasMatch()) {
            int length = match.capturedLength();
            setFormat(index, length, rule.color);
            match = expression.match(text, index + length);
            index = match.capturedStart();
        }
    }
}
