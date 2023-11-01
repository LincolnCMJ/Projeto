char* generate_json() {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "schema", 1);
    cJSON_AddNumberToObject(root, "data", -20.3110973);
    cJSON_AddNumberToObject(root, "data", -40.3211573);
    cJSON_AddStringToObject(root, "date", "2023-01-01T00:00:00.000-03:00");

    char *json_string = cJSON_Print(root);
    //printf(json_string);
    return json_string;
}
