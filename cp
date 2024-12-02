variable "secret_name" {
  description = "Le nom du secret"
  type        = string

  validation {
    condition     = can(regex("^[a-zA-Z0-9/_+=.@-]+$", var.secret_name))
    error_message = "Le nom du secret ne peut contenir que des caractères alphanumériques et les symboles /_+=.@-."
  }
}
