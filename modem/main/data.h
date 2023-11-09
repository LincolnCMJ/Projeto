char* geolocation() {
    cJSON *new_array = cJSON_CreateArray();

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "schema", 1);

    cJSON *data = cJSON_CreateObject();
    cJSON_AddNumberToObject(data, "latitude", -20.2878013);
    cJSON_AddNumberToObject(data, "longitude", -40.2931247);
    cJSON_AddItemToObject(root, "data", data);

    cJSON_AddStringToObject(root, "date", "2023-01-10T00:00:00.000-03:00");

    cJSON_AddItemToArray(new_array, root);

    char *json_string = cJSON_Print(new_array);
    return json_string;
}
