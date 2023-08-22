from pygments.lexer import RegexLexer, bygroups, words, include
from pygments.token import *

class CustomLexer(RegexLexer):
    name = 'Prepro'
    aliases = ['prepro']
    filenames = []

    tokens = {
        'phase3': [
            (r'\w+', Name),
            (r'\d[0-9a-zA-Z+-.]*', Number),
            (r"'[^']+'", String.Char),
            (r'"[^"]*"', String),
        ],
        'detect_comment': [
            (r'/[*]', Comment.Multiline, 'comment'),
            (r'//.*?$', Comment.Single),
        ],
        'detect_prepro' : [
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
             ('prepro', 'param_list')),
            (r'^(#)(\w*if\w*|el[si][ef])(\s+)$',
             bygroups(Comment.Hashbang,
                      Keyword,
                      Whitespace)),
            (r'^(#)(.*)$',
             bygroups(Comment.Hashbang,
                      Comment.Preproc)),
        ],
        'root': [
            include('phase3'),
            include('detect_comment'),
            include('detect_prepro'),
            ('defined', Keyword.Reserved),
        ],
        'param_list': [
            include('detect_comment'),
            (r'\w+', Name.Variable),
            (r'\s+', Whitespace),
            (r',', Punctuation),
            (r'[.]{3}', Operator),
            (r'[)]', Punctuation, '#pop')
        ],
        'prepro' : [
            include('detect_comment'),
            (r'(\w+)(\s*)([(])', bygroups(Name.Function, Whitespace, Punctuation)),
            (r'[A-Z_]+\b', Name.Constant),
            (r'\w+', Name),
            (r'[#]+', Operator),
            (r'[)(,]+', Punctuation),
            (words(('__VA_ARGS__', '__VA_OPT__'), suffix=r'\b'), Name.Variable.Magic),
        ],
        'comment' : [
            (r'[^*]+', Comment.Multiline),
            (r'[*]/', Comment.Multiline, '#pop'),
            (r'[*]', Comment.Multiline),
        ]
    }
