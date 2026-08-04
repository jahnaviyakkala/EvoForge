import pytest
from UserManagementService import User, UserRepository, UserManagementService

def test_create_user():
    user_repo = UserRepository()
    user_service = UserManagementService(user_repo)
    
    # Positive case
    assert user_service.create_user("testuser", "test@example.com") == True
    user = user_repo.get_user_by_id(1)
    assert user is not None
    assert user.username == "testuser"
    assert user.email == "test@example.com"

    # Duplicate user ID (negative case)
    assert user_service.create_user("testuser2", "test2@example.com") == True
    assert user_service.create_user("testuser3", "test3@example.com") == False

def test_get_user():
    user_repo = UserRepository()
    user_service = UserManagementService(user_repo)
    
    # Positive case
    user_service.create_user("testuser", "test@example.com")
    user = user_service.get_user(1)
    assert user is not None
    assert user.username == "testuser"
    assert user.email == "test@example.com"

    # Non-existent user ID (negative case)
    user = user_service.get_user(2)
    assert user is None

def test_update_user():
    user_repo = UserRepository()
    user_service = UserManagementService(user_repo)
    
    # Positive case
    user_service.create_user("testuser", "test@example.com")
    assert user_service.update_user(1, "newusername", "newemail@example.com") == True
    user = user_repo.get_user_by_id(1)
    assert user is not None
    assert user.username == "newusername"
    assert user.email == "newemail@example.com"

    # Non-existent user ID (negative case)
    assert user_service.update_user(2, "anotheruser", "anotheremail@example.com") == False

def test_invalid_inputs():
    user_repo = UserRepository()
    user_service = UserManagementService(user_repo)
    
    # Invalid username and email
    with pytest.raises(ValueError):
        user_service.create_user("", "")
    with pytest.raises(ValueError):
        user_service.update_user(1, "", "")

if __name__ == "__main__":
    pytest.main()
