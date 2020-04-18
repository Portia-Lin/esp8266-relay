const char CONFIG_DEVICE[] PROGMEM = R"=====(
<!DOCTYPE html>

<head>
  <title>Device</title>
  <meta charset="UTF-8">
  <meta name="viewport" content="width = device-width, initial-scale = 1.0, maximum-scale = 1.0">
  <style>
    body {
      background-color: #F7F9FD;
    }

    .container {
      width: 20rem;
      margin-left: auto;
      margin-right: auto;
      margin-bottom: 4rem;
    }

    .left {
      margin-left: 1rem;
    }

    .center {
      text-align: center;
    }

    input[type=text] {
      width: 18rem;
      border: 0.05rem solid #000;
      border-radius: 0.5rem;
      padding: 0.7rem 1rem;
      outline:none;
    }

    input[type=text]:focus {
      border: 0.05rem dashed #000;
    }

    input[type=button] {
      display: block;
      width: 40%;
      padding: 0.5rem;
      border: 0.1rem solid #000;
      border-radius: 0.5rem;
      background-color: #F7F9FD;
      font-family: 'Montserrat', sans-serif;
      font-size: 11pt;
      font-weight: bold;
      letter-spacing: 0.2rem;
      text-align: center;
      text-decoration: none;
      outline: none;
      float: left;
    }

    input[type=button]:active {
      border-color: #1A1A1A;
      background-color: #1A1A1A;
      color: white;
    }

    a {
      margin-left: 1rem;
      text-decoration: none;
      outline: none;
      float: right;
    }

  </style>
</head>

<body onload="loadDevice();">
  <div class="container">
    <h2 class="center"><b>Device properties</b></h2><br>
    <p class="left">Device name:</p>
    <input type="text" id="d_name" placeholder="device name">
    <p class="left">Hostname:</p>
    <input type="text" id="d_hostname" placeholder="hostname"><br><br>
    <p class="left">Uptime: <span id='d_uptime'>---</span> m.</p>
    <p class="left">IP Address: <span id='d_ip'>---</span></p>
    <p class="left">MAC Address: <span id='d_mac'>---</span></p>
    <br><br>
    <input onclick="saveDevice();" type="button" id="sendbtn" value="SUBMIT">
    <!-- home -->
    <a href="/">
      <img src="data:image/svg+xml;utf8;base64,PHN2ZyBoZWlnaHQ9IjUxMnB0IiB2aWV3Qm94PSIwIDAgNTEyIDUxMi4wMTA2NyIgd2lkdGg9IjUxMnB0IiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciPjxwYXRoIGQ9Im00MTAuNjcxODc1IDUxMi4wMTE3MTloLTg1LjMzMjAzMWMtOC44MzIwMzIgMC0xNi03LjE2Nzk2OS0xNi0xNnYtMTM4LjY2Nzk2OWMwLTIuOTQ1MzEyLTIuMzkwNjI1LTUuMzMyMDMxLTUuMzM1OTM4LTUuMzMyMDMxaC05NmMtMi45NDE0MDYgMC01LjMzMjAzMSAyLjM4NjcxOS01LjMzMjAzMSA1LjMzMjAzMXYxMzguNjY3OTY5YzAgOC44MzIwMzEtNy4xNjc5NjkgMTYtMTYgMTZoLTg1LjMzMjAzMWMtMjAuNTg1OTM4IDAtMzcuMzM1OTM4LTE2Ljc0NjA5NC0zNy4zMzU5MzgtMzcuMzM1OTM4di0xOTcuMzMyMDMxaC0zNy4zMzIwMzFjLTE0LjY5OTIxOSAwLTI2LjY2Nzk2ODc1LTExLjk2ODc1LTI2LjY2Nzk2ODc1LTI2LjY2Nzk2OSAwLTcuMDU4NTkzIDIuODgyODEyNzUtMTMuOTcyNjU2IDcuODk0NTMxNzUtMTguOTg0Mzc1bDIzNy4wMzUxNTYtMjI3LjI0MjE4N2M2LjE4NzUtNS45MzM1OTQgMTUuOTU3MDMxLTUuOTMzNTk0IDIyLjE0NDUzMSAwbDIzNi44MDA3ODEgMjI2Ljk4NDM3NWM1LjI0NjA5NCA1LjI2OTUzMSA4LjEyNSAxMi4xODM1OTQgOC4xMjUgMTkuMjQyMTg3IDAgMTQuNjk5MjE5LTExLjk2NDg0NCAyNi42Njc5NjktMjYuNjY0MDYyIDI2LjY2Nzk2OWgtMzcuMzM1OTM4djE5Ny4zMzIwMzFjMCAyMC41ODk4NDQtMTYuNzQ2MDk0IDM3LjMzNTkzOC0zNy4zMzIwMzEgMzcuMzM1OTM4em0tNjkuMzMyMDMxLTMyaDY5LjMzMjAzMWMyLjkwMjM0NCAwIDUuMzMyMDMxLTIuNDMzNTk0IDUuMzMyMDMxLTUuMzM1OTM4di0yMTMuMzMyMDMxYzAtOC44MzIwMzEgNy4xNjc5NjktMTYgMTYtMTZoNDAuMTI4OTA2bC0yMTYuMTI4OTA2LTIwNy4xNjc5NjktMjE2LjEyNSAyMDcuMTY3OTY5aDQwLjEyNWM4LjgzMjAzMiAwIDE2IDcuMTY3OTY5IDE2IDE2djIxMy4zMzIwMzFjMCAyLjkwMjM0NCAyLjQzMzU5NCA1LjMzNTkzOCA1LjMzNTkzOCA1LjMzNTkzOGg2OS4zMzIwMzF2LTEyMi42Njc5NjljMC0yMC41ODU5MzggMTYuNzQ2MDk0LTM3LjMzMjAzMSAzNy4zMzIwMzEtMzcuMzMyMDMxaDk2YzIwLjU4OTg0NCAwIDM3LjMzNTkzOCAxNi43NDYwOTMgMzcuMzM1OTM4IDM3LjMzMjAzMXptMCAwIi8+PC9zdmc+" style="width:2rem;">
    </a>
    <!-- mqtt -->
    <a href="configMqtt">
      <img src="data:image/svg+xml;utf8;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iaXNvLTg4NTktMSI/Pg0KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDE5LjAuMCwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPg0KPHN2ZyB2ZXJzaW9uPSIxLjEiIGlkPSJMYXllcl8xIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHhtbG5zOnhsaW5rPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5L3hsaW5rIiB4PSIwcHgiIHk9IjBweCINCgkgdmlld0JveD0iMCAwIDQ5MC42NjcgNDkwLjY2NyIgc3R5bGU9ImVuYWJsZS1iYWNrZ3JvdW5kOm5ldyAwIDAgNDkwLjY2NyA0OTAuNjY3OyIgeG1sOnNwYWNlPSJwcmVzZXJ2ZSI+DQo8Zz4NCgk8Zz4NCgkJPHBhdGggZD0iTTI0NS4zMzMsMEMxMTAuMDU5LDAsMCwxMTAuMDU5LDAsMjQ1LjMzM3MxMTAuMDU5LDI0NS4zMzMsMjQ1LjMzMywyNDUuMzMzczI0NS4zMzMtMTEwLjA1OSwyNDUuMzMzLTI0NS4zMzMNCgkJCVMzODAuNjA4LDAsMjQ1LjMzMywweiBNMjQ1LjMzMyw0NjkuMzMzYy0xMjMuNTIsMC0yMjQtMTAwLjQ4LTIyNC0yMjRzMTAwLjQ4LTIyNCwyMjQtMjI0czIyNCwxMDAuNDgsMjI0LDIyNA0KCQkJUzM2OC44NTMsNDY5LjMzMywyNDUuMzMzLDQ2OS4zMzN6Ii8+DQoJPC9nPg0KPC9nPg0KPGc+DQoJPGc+DQoJCTxwYXRoIGQ9Ik0yNDUuMzMzLDBjLTc3Ljc2LDAtMTM4LjY2NywxMDcuNzU1LTEzOC42NjcsMjQ1LjMzM3M2MC45MDcsMjQ1LjMzMywxMzguNjY3LDI0NS4zMzNTMzg0LDM4Mi45MTIsMzg0LDI0NS4zMzMNCgkJCVMzMjMuMDkzLDAsMjQ1LjMzMywweiBNMjQ1LjMzMyw0NjkuMzMzYy02My41OTUsMC0xMTcuMzMzLTEwMi41OTItMTE3LjMzMy0yMjRzNTMuNzM5LTIyNCwxMTcuMzMzLTIyNA0KCQkJczExNy4zMzMsMTAyLjU5MiwxMTcuMzMzLDIyNFMzMDguOTI4LDQ2OS4zMzMsMjQ1LjMzMyw0NjkuMzMzeiIvPg0KCTwvZz4NCjwvZz4NCjxnPg0KCTxnPg0KCQk8cGF0aCBkPSJNMjQ1LjMzMywwYy01Ljg4OCwwLTEwLjY2Nyw0Ljc3OS0xMC42NjcsMTAuNjY3VjQ4MGMwLDUuODg4LDQuNzc5LDEwLjY2NywxMC42NjcsMTAuNjY3UzI1Niw0ODUuODg4LDI1Niw0ODBWMTAuNjY3DQoJCQlDMjU2LDQuNzc5LDI1MS4yMjEsMCwyNDUuMzMzLDB6Ii8+DQoJPC9nPg0KPC9nPg0KPGc+DQoJPGc+DQoJCTxwYXRoIGQ9Ik00ODAsMjM0LjY2N0gxMC42NjdDNC43NzksMjM0LjY2NywwLDIzOS40NDUsMCwyNDUuMzMzUzQuNzc5LDI1NiwxMC42NjcsMjU2SDQ4MGM1Ljg4OCwwLDEwLjY2Ny00Ljc3OSwxMC42NjctMTAuNjY3DQoJCQlTNDg1Ljg4OCwyMzQuNjY3LDQ4MCwyMzQuNjY3eiIvPg0KCTwvZz4NCjwvZz4NCjxnPg0KCTxnPg0KCQk8cGF0aCBkPSJNNDM3LjMzMywxMDYuNjY3aC0zODRjLTUuODg4LDAtMTAuNjY3LDQuNzc5LTEwLjY2NywxMC42NjdTNDcuNDQ1LDEyOCw1My4zMzMsMTI4aDM4NA0KCQkJYzUuODg4LDAsMTAuNjY3LTQuNzc5LDEwLjY2Ny0xMC42NjdTNDQzLjIyMSwxMDYuNjY3LDQzNy4zMzMsMTA2LjY2N3oiLz4NCgk8L2c+DQo8L2c+DQo8Zz4NCgk8Zz4NCgkJPHBhdGggZD0iTTQzNy4zMzMsMzYyLjY2N2gtMzg0Yy01Ljg4OCwwLTEwLjY2Nyw0Ljc3OS0xMC42NjcsMTAuNjY3YzAsNS44ODgsNC43NzksMTAuNjY3LDEwLjY2NywxMC42NjdoMzg0DQoJCQljNS44ODgsMCwxMC42NjctNC43NzksMTAuNjY3LTEwLjY2N0M0NDgsMzY3LjQ0NSw0NDMuMjIxLDM2Mi42NjcsNDM3LjMzMywzNjIuNjY3eiIvPg0KCTwvZz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjwvc3ZnPg0K" style="width:2rem;">
    </a>
    <div class="info">
      
    </div>
  </div>
</body>
<script>
  function saveDevice() {
    var xhr = new XMLHttpRequest();
    var params = 'd_name=' + d_name.value + '&d_hostname=' + d_hostname.value;
    xhr.open("POST", '/saveDevice?' + params);
    xhr.send();
    alert('Changes will be applied after reboot.');
  }

  function loadDevice() {
    var xhr = new XMLHttpRequest();
    xhr.open("POST", '/loadDevice');
    xhr.send(null);
    xhr.onload = function() {
      if (xhr.status == 200) {
        var json = JSON.parse(xhr.response);
        document.getElementById('d_name').value = json.d_name;
        document.getElementById('d_hostname').value = json.d_hostname;
        document.getElementById('d_uptime').innerHTML = Math.floor(json.uptime/60000);
        document.getElementById('d_ip').innerHTML = json.d_ip;
        document.getElementById('d_mac').innerHTML = json.d_mac;
      }
    };
  }
</script>

</html>
)=====";
