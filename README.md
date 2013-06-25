# What's echo-q #

echo-q is a simple, lightweight message queue **SERVICE**.

it enable us to transfer the message from different server(*or Process*) more easily!

**echoq** is both a server and a client. a echoq service can send/recv message from another service.

- - -

this communication model is supported in **echoq** :

1. pipeline ( **only for interprocess communication** )
2. publisher/subscribe
3. broadcast in Group (like a chatroom)
4. request-reply

# Guide

[Chinese Version](user_guide_zhCN.md)

# How to Use

status:

      $ echoq -status

today's log:

      $ echoq -log


# Example Code

although echoq is written by **C++**, but it also has **other languages bindings**. 

The one of these languages is **Python** :

```python

      # get echoq's context, and create a subscribe service to listen the 192.168.1.100
      ctx = echoq.context()
      serv = ctx.listen('sub://192.168.1.100')

```

