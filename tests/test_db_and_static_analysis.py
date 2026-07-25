import os
import ast
import tempfile
from database.db_manager import DBManager
from tools.static_analysis import _annotate_parents, _collect_call_edges

def test_db_manager_new_methods():
    fd, temp_db_path = tempfile.mkstemp()
    os.close(fd)
    try:
        db = DBManager(db_path=temp_db_path)
        project_id = db.register_project("test_project", "/fake/path")
        
        # Test store_srs_version
        srs_id = db.store_srs_version(project_id, "# My Test SRS\n- Req 1", note="new")
        assert srs_id is not None
        
        # Test store_dependency_graph
        graph_id = db.store_dependency_graph(project_id, "static", '{"modules": {}}')
        assert graph_id is not None
        
        # Verify db persistence
        with db.get_connection() as conn:
            srs_rows = conn.execute("SELECT version, content FROM srs_versions").fetchall()
            assert len(srs_rows) == 1
            assert srs_rows[0][0] == 1
            assert "Req 1" in srs_rows[0][1]
            
            graph_rows = conn.execute("SELECT graph_type, graph_json FROM dependency_graphs").fetchall()
            assert len(graph_rows) == 1
            assert graph_rows[0][0] == "static"
    finally:
        if os.path.exists(temp_db_path):
            os.remove(temp_db_path)

def test_collect_call_edges_nested():
    code = """
def test_function():
    x = 10
    if x > 5:
        nested_call()
    return another_call()
"""
    tree = ast.parse(code)
    _annotate_parents(tree)
    edges = _collect_call_edges(tree)
    
    # We expect caller for nested_call and another_call to be 'test_function' instead of '<unknown>'
    assert len(edges) == 2
    assert {"caller": "test_function", "callee": "nested_call"} in edges
    assert {"caller": "test_function", "callee": "another_call"} in edges
