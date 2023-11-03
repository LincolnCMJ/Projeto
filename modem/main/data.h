char* generate_json() {
    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "schema", 1);

    cJSON *data = cJSON_CreateObject();
    cJSON_AddNumberToObject(data, "latitude", -20.2878013);
    cJSON_AddNumberToObject(data, "longitude", -40.2931247);
    cJSON_AddItemToObject(root, "data", data);

    cJSON_AddStringToObject(root, "date", "2023-11-2T00:00:00.000-03:00");

    char *json_string = cJSON_Print(root);
    return json_string;
}
