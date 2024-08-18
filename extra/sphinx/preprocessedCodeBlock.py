from collections.abc import Sequence

from docutils import nodes
from docutils.parsers.rst import directives

from sphinx.application import Sphinx
from sphinx.util.docutils import SphinxDirective
from sphinx.util.typing import ExtensionMetadata
from sphinx.directives.code import LiteralInclude
from sphinx.directives.other import Include
#from docutils.parsers.rst.directives.misc import Include

from myst_parser.parsers.docutils_ import Parser as MystParser

def create_sphinx_design_component(name: str, classes: list[str], rawtext: str = ""):
    return nodes.container(rawtext, is_div=True, design_component=name, classes=classes)

def create_tab_set(named_nodes: Sequence[(str, nodes.Node)]):
    tab_set = create_sphinx_design_component('tab-set', classes=['sd-tab-set'])
    for name, node in named_nodes:
        tab_item = create_sphinx_design_component('tab-item', classes=['sd-tab-item'])
        tab_label = nodes.rubric(name, nodes.Text(name), classes=['sd-tab-label'])
        tab_content = create_sphinx_design_component('tab-content', classes=['sd-tab-content'])
        tab_content += node
        tab_item += [tab_label, tab_content]
        tab_set += tab_item
    return [tab_set]

class PreprocessedCodeBlock(SphinxDirective):
    """
    Showcase a code block with 4 tabs:
     - Compiler view: C syntax highlight
     - Preprocessor view: Custom syntax highlight
     - Preprocessed: Show the output of the preprocessor
     - Output: The standard output of the execution

    For now it relies on an external makefile having generated the preprocessed and output.
    TODO: Do it from here and support inline code bock
    """
    has_content = False
    required_arguments = 1
    optional_arguments = 0
    option_spec = {
        #'sync': directives.flag
    }

    def literal_include(self, name: str, filename: str, options: dict):
        return LiteralInclude(name,
                              [filename],
                              options,
                              self.content,
                              self.lineno,
                              self.content_offset,
                              self.block_text,
                              self.state,
                              self.state_machine).run()

    def run(self) -> list[nodes.Node]:
        filename = self.arguments[0]

        compiler_view = self.literal_include('compiler-view',
                                             f'../samples/{filename}.c',
                                             {'language': 'C', 'linenos': True})
        prepro_view = self.literal_include('prepro-view',
                                           f'../samples/{filename}.c',
                                           {'language': 'prepro', 'linenos': True})
        preprocessed = self.literal_include('preprocessed',
                                           f'../preprocessed/{filename}.i',
                                           {'language': 'C'})
        output = Include(self.name,
                         [f'../outputs/{filename}.txt'],
                         {'parser':MystParser},
                         self.content, self.lineno, self.content_offset,
                         self.block_text, self.state, self.state_machine).run()

        return create_tab_set([('Compiler view', compiler_view),
                               ('Preprocessor view', prepro_view),
                               ('Preprocessed', preprocessed),
                               ('Output', output)])


def setup(app: Sphinx) -> ExtensionMetadata:
    app.add_directive('preprocessed', PreprocessedCodeBlock)

    return {
        'version': '0.1',
        'parallel_read_safe': True,
        'parallel_write_safe': True
    }
