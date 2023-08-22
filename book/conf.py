# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

import sys
import os

from sphinx.highlighting import lexers

sys.path.append('../extra/pygment')
from lexer import CustomLexer as PreproLexer

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'Black Magic'
copyright = '2023'
author = 'Antoine Gagniere'
release = os.environ.get('PROJECT_VERSION', 'Unknown')
language = 'en'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
    'myst_parser',
    'sphinx_copybutton',
    'sphinx_design',
]

templates_path = ['_templates']
exclude_patterns = []

primary_domain = 'c'

source_suffix = {'.rst': 'restructuredtext', '.md': 'markdown'}

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme       = 'sphinx_book_theme'
html_static_path = ['_static']
html_logo        = 'assets/logo.png'

html_theme_options = {
    'navigation_with_keys': True,
}

# -- Myst Parser Options -----------------------------------------------------

# Allows writing ```mermaid instead of ```{mermaid}, keeping compatibility with GitLab
#myst_fence_as_directive = ['mermaid']

myst_enable_extensions = ['attrs_inline', 'attrs_block', 'colon_fence']

myst_heading_anchors = 4

myst_words_per_minute = 150

#

# mermaid_output_format = 'svg'

# -- Pygment customization ---------------------------------------------------

lexers['prepro'] = PreproLexer()
