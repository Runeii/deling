import os
import re

def migrate_qregexp_to_qregular_expression(file_path):
    with open(file_path, 'r') as file:
        content = file.read()

    # Replace QRegExp includes with QRegularExpression
    content = re.sub(r'#include\s+<QRegExp>', '#include <QRegularExpression>', content)

    # Replace QRegExp object declarations with QRegularExpression
    content = re.sub(r'\bQRegExp\b', 'QRegularExpression', content)

    # Handle constructor replacements
    content = re.sub(r'QRegularExpression\s*\(\s*"(.+?)"\s*\)',
                     r'QRegularExpression(QStringLiteral(r"\1"))', content)

    # Handling methods that were common in QRegExp and their equivalent in QRegularExpression
    replacements = {
        r'\.exactMatch\(': r'.match(',  # Remove group reference, adjust according to usage in code
        r'\.indexIn\(': r'.match(',  # Remove group reference
        r'\.cap\(': r'.match(',  # Remove group reference
        r'\.captureCount\(': r'.match(',  # Remove group reference
        r'\.isValid\(': r'.isValid(',
        r'\.pattern\(': r'.pattern(',
        r'\.setPattern\(': r'.setPattern(',
        r'\.patternSyntax\(': r'.patternOptions(',
        r'\.setPatternSyntax\(': r'.setPatternOptions('
    }

    for old, new in replacements.items():
        content = re.sub(old, new, content)

    with open(file_path, 'w') as file:
        file.write(content)

    print("File " + file_path + " migrated successfully.")

def migrate_directory(directory):
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith('.cpp') or file.endswith('.h'):
                file_path = os.path.join(root, file)
                migrate_qregexp_to_qregular_expression(file_path)

if __name__ == "__main__":
    directory = input("Enter the directory to migrate: ")
    migrate_directory(directory)

