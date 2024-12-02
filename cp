# Génération d'un mot de passe aléatoire
resource "random_password" "random_role_password" {
  length  = 22
  special = false
}

# Définition du secret dans AWS Secrets Manager
resource "aws_secretsmanager_secret" "secret_role_password" {
  name = var.secret_name
}

# Version du secret avec le mot de passe généré
resource "aws_secretsmanager_secret_version" "secret_role_password" {
  secret_id     = aws_secretsmanager_secret.secret_role_password.id
  secret_string = random_password.random_role_password.result
}
