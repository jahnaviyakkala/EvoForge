import pytest
from UserManagementService import User, UserRepository, UserManagementService

def test_create_user_in_main():
    user_repo = UserRepository()
    user_service = UserManagementService(user_repo)
    
    # Positive case
    assert user_service.create_user("testuser", "test@example.com") == True
    user = user_repo.get_user_by_id(1)
    assert user is not None
    assert user.username == "testuser"
    assert user.email == "test@example.com"

def test_get_user_in_main():
    user_repo = UserRepository()
    user_service = UserManagementService(user_repo)
    
    # Positive case
    user_service.create_user("testuser", "test@example.com")
    user = user_service.get_user(1)
    assert user is not None
    assert user.username == "testuser"
    assert user.email == "test@example.com"

def test_update_user_in_main():
    user_repo = UserRepository()
    user_service = UserManagementService(user_repo)
    
    # Positive case
    user_service.create_user("testuser", "test@example.com")
    assert user_service.update_user(1, "newusername", "newemail@example.com") == True
    user = user_repo.get_user_by_id(1)
    assert user is not None
    assert user.username == "newusername"
    assert user.email == "newemail@example.com"

def test_invalid_inputs_in_main():
    user_repo = UserRepository()
    user_service = UserManagementService(user_repo)
    
    # Invalid username and email
    with pytest.raises(ValueError):
        user_service.create_user("", "")
    with pytest.raises(ValueError):
        user_service.update_user(1, "", "")

if __name__ == "__main__":
    pytest.main()
