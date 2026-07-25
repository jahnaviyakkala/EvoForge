import os
import pytest
from tools.cli_ui import (
    is_rich_available,
    fetch_project_portfolio,
    get_project_inspect_info,
    print_banner,
    print_triage_result,
    print_verification_summary,
    print_projects_portfolio,
    print_system_diagnostics
)

def test_is_rich_available():
    assert is_rich_available() is True

def test_fetch_project_portfolio():
    portfolio = fetch_project_portfolio()
    assert isinstance(portfolio, list)
    if portfolio:
        item = portfolio[0]
        assert "name" in item
        assert "path" in item
        assert "language" in item
        assert "file_count" in item
        assert "has_srs" in item

def test_get_project_inspect_info():
    project_dir, reports_dir, files_list, srs_content = get_project_inspect_info("calculator")
    assert "calculator" in project_dir
    assert isinstance(files_list, list)

def test_print_functions_do_not_crash(capsys):
    print_banner()
    print_triage_result("test_proj", "new", "python")
    print_verification_summary(
        project_name="test_proj",
        language="python",
        compile_success=True,
        compile_output="",
        test_success=True,
        test_output="1 passed in 0.01s"
    )
    print_projects_portfolio([
        {"name": "demo", "language": "python", "file_count": 2, "has_srs": True, "path": "/tmp/demo"}
    ])
    print_system_diagnostics({"LLM_PROVIDER": "ollama"}, "Connected", True)
    captured = capsys.readouterr()
    assert len(captured.out) > 0
