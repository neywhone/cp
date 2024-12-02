 Error: Invalid value for variable
│ 
│   on vector-db.tf line 4, in module "vector_db":
│    4:     secret_name = "secret-ceos-vector-$(each.key)-database-password"
│     ├────────────────
│     │ var.secret_name is "secret-ceos-vector-$(each.key)-database-password"
│ 
│ Le nom du secret ne peut contenir que des caractères alphanumériques et les symboles /_+=.@-.
│ 
│ This was checked by the validation rule at modules/vector-db/variables.tf:9,3-13.
