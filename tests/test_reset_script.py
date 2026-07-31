import os
import shutil
from reset import reset_workspace
from database.db_manager import DBManager

def test_reset_workspace_clears_directories_and_db(tmp_path):
    projects_dir = os.path.join(os.path.dirname(__file__), "..", "projects")
    reports_dir = os.path.join(os.path.dirname(__file__), "..", "reports")
    
    # Create dummy items
    dummy_proj = os.path.join(projects_dir, "dummy_project")
    dummy_rep = os.path.join(reports_dir, "dummy_project")
    os.makedirs(dummy_proj, exist_ok=True)
    os.makedirs(dummy_rep, exist_ok=True)
    
    with open(os.path.join(dummy_proj, "test.txt"), "w") as f:
        f.write("test")
    with open(os.path.join(dummy_rep, "SRS.md"), "w") as f:
        f.write("# SRS")

    # Run reset
    reset_workspace()

    assert not os.path.exists(dummy_proj)
    assert not os.path.exists(dummy_rep)
    
    # Verify DB connection works after reset
    db = DBManager()
    with db.get_connection() as conn:
        cursor = conn.cursor()
        cursor.execute("SELECT name FROM sqlite_master WHERE type='table';")
        tables = [row[0] for row in cursor.fetchall()]
        assert "projects" in tables
        assert "file_registry" in tables
