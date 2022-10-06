from uwsgi import start_response


def application(_, start_response):
    start_response('200 OK', [('Content-Type', 'text/html')])
    return ["""
<!DOCTYPE html>
<html>
	<head>
		<title>Super website</title>
	</head>
	<body>
		<h1>Super securized HTTP website</h1>
		<p>Enter your bank account, by logged in bellow:</p>
	</body>
	<!-- Login form ... -->
</html>
""".encode()]
