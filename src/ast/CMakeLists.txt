

target_sources(libshaker PUBLIC
    annotation_node.cpp
    expression_node.cpp
    function_node.cpp
    node.cpp
    print_visitor.cpp
    printer/annotation_printer.cpp
    printer/hlsl_printer.cpp
    printer/xlsl_printer.cpp
    statement_node.cpp
    technique_node.cpp
    tree_traverser.cpp)

target_include_directories(libshaker PUBLIC . )