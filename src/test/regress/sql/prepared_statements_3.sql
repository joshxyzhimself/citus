SET search_path TO "prepared statements";

-- test function evaluation with parameters in an expression
PREPARE prepared_function_evaluation_insert(int) AS
	INSERT INTO prepare_func_table (key, value1) VALUES ($1+1, 0*random());

-- execute 7 times to trigger prepared statement usage
EXECUTE prepared_function_evaluation_insert(1);
EXECUTE prepared_function_evaluation_insert(2);
EXECUTE prepared_function_evaluation_insert(3);
EXECUTE prepared_function_evaluation_insert(4);
EXECUTE prepared_function_evaluation_insert(5);
EXECUTE prepared_function_evaluation_insert(6);
EXECUTE prepared_function_evaluation_insert(7);

SELECT key, value1 FROM prepare_func_table ORDER BY key, value1;
TRUNCATE prepare_func_table;

-- make it a bit harder: parameter wrapped in a function call
PREPARE wrapped_parameter_evaluation(text,text[]) AS
	INSERT INTO prepare_func_table (key,value2) VALUES ($1,array_to_string($2,''));

EXECUTE wrapped_parameter_evaluation('key', ARRAY['value']);
EXECUTE wrapped_parameter_evaluation('key', ARRAY['value']);
EXECUTE wrapped_parameter_evaluation('key', ARRAY['value']);
EXECUTE wrapped_parameter_evaluation('key', ARRAY['value']);
EXECUTE wrapped_parameter_evaluation('key', ARRAY['value']);
EXECUTE wrapped_parameter_evaluation('key', ARRAY['value']);
EXECUTE wrapped_parameter_evaluation('key', ARRAY['value']);

SELECT key, value2 FROM prepare_func_table ORDER BY key, value2;

