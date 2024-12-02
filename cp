resource "random_password" "random_role_password" {
  # longer length instead of special chars to ease inclusion in URI connection strings
  length  = 22
  special = false
}

resource "aws_secretsmanager_secret" "secret_role_password" {
  name = var.secret_name
}
resource "aws_secretsmanager_secret_version" "secret_role_password" {
  secret_id     = aws_secretsmanager_secret.secret_role_password.id
  secret_string = random_password.random_role_password.result
}
│ Error: only alphanumeric characters and /_+=.@- special characters are allowed in "name"
│ 
│   with module.vector_db["core"].aws_secretsmanager_secret.secret_role_password,
│   on modules/vector-db/secrets.tf line 8, in resource "aws_secretsmanager_secret" "secret_role_password":
│    8:   name = var.secret_name
│ 
╵
╷
│ Error: only alphanumeric characters and /_+=.@- special characters are allowed in "name"
│ 
│   with module.vector_db["develop"].aws_secretsmanager_secret.secret_role_password,
│   on modules/vector-db/secrets.tf line 8, in resource "aws_secretsmanager_secret" "secret_role_password":
│    8:   name = var.secret_name
│ 
╵
╷
│ Error: only alphanumeric characters and /_+=.@- special characters are allowed in "name"
│ 
│   with module.vector_db["uat"].aws_secretsmanager_secret.secret_role_password,
│   on modules/vector-db/secrets.tf line 8, in resource "aws_secretsmanager_secret" "secret_role_password":
│    8:   name = var.secret_name
│ 
