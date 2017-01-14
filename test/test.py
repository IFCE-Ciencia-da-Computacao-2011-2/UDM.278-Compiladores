import subprocess
import unittest

import re


class Test(unittest.TestCase):
    def execute(self, codigo):
        call = ['./vando']

        process = subprocess.Popen(call, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        process.stdin.write(bytes(codigo.strip(), 'UTF-8'))

        out, error = process.communicate()

        return out.decode('UTF-8'), error.decode('UTF-8').strip()

    def escape(self, message):
        return re.compile(r'\x1b[^m]*m').sub('', message)

    def assert_raises_error(self, code, error):
        process_out, process_error = self.execute(code)

        print(process_error)

        self.assertEqual(error.strip(), self.escape(process_error))