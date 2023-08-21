from pygments.lexer import RegexLexer, bygroups
from pygments.token import *

class CustomLexer(RegexLexer):
    name = 'Prepro'
    aliases = ['prepro']
    filenames = ['*.i']

    tokens = {
        'root': [
            ('defined', Keyword.Reserved),
            (r'^(#)(include)(\s+)([<"][\w/.]+[">])',
             bygroups(Comment.Hashbang,
                      Keyword,
                      Whitespace,
                      Comment.PreprocFile)),
            (r'^(#)(define)(\s+)(\w+)(\s+)',
             bygroups(Comment.Hashbang,
                      Keyword,
                      Whitespace,
                      Name.Constant,
                      Whitespace),
             'prepro'),
            (r'^(#)(define)(\s+)(\w+)([(])',
             bygroups(Comment.Hashbang,
                      Keyword,
                      Whitespace,
                      Name.Function,
                      Punctuation),
             'param_list'),
            (r'^(#)(\w*if\w*|el[si][ef])(\s+)(.*)$',
             bygroups(Comment.Hashbang,
                      Keyword,
                      Whitespace,
                      Comment.Preproc)),
            (r'^(#)(.*)$',
             bygroups(Comment.Hashbang,
                      Comment.Preproc)),

            (r'\w+', Name),
            (r'\d[0-9a-zA-Z+-.]*', Number),
            (r"'[^']+'", String.Char),
            (r'"[^"]*"', String),
        ],
        'param_list': [
            (',', Punctuation),
            (r'\w+', Name.Variable),
            (r'\s+', Whitespace),
            (r'...', Operator),
            (r'[)]', Punctuation, 'prepro')
        ],
        'prepro' : [
            (r'\(|\)', Punctuation),
            (r'[#]+', Operator),
            (r'\w+', Name),
            ('\n', Whitespace, '#pop'),
        ]
    }
