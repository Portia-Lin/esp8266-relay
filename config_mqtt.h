const char CONFIG_MQTT[] PROGMEM = R"=====(
<!DOCTYPE html>

<head>
  <title>MQTT Client</title>
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

    .checkbox {
      position: relative;
      padding-left: 25px;
    }

    .checkbox input[type=checkbox] {
      display: none;
    }

    .checkbox label:after {
      content: '';
      display: block;
      height: 14px;
      width: 14px;
      outline: 1px solid #000;
      position: absolute;
      top: 0;
      left: 0;
    }

    .checkbox input[type=checkbox]:checked + label:after {
      outline: 1px solid #000;
      border: 2px solid #fff;
      width: 10px;
      height: 10px;
      background-color: #000;
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

<body onload="loadConfig();">
  <div class="container">
    <h2 class="center"><b>MQTT Client properties</b></h2><br>
    <div class="checkbox left">
      <input onclick="saveStatus();" type="checkbox" id="check"><label for="check">Enable MQTT connection</label>
    </div>
    <p class="left">MQTT Server:</p>
    <input type="text" id="mqtt_server" placeholder="mqtt server">
    <p class="left">MQTT Port:</p>
    <input type="text" id="mqtt_port" placeholder="mqtt port">
    <p class="left">MQTT User:</p>
    <input type="text" id="mqtt_user" placeholder="mqtt user">
    <p class="left">MQTT Password:</p>
    <input type="text" id="mqtt_password" placeholder="mqtt password">
    <br><br><br><br>
    <input onclick="saveConfig();" type="button" id="sendbtn" value="SUBMIT">
    <!-- home -->
    <a href="/">
      <img src="data:image/svg+xml;utf8;base64,PHN2ZyBoZWlnaHQ9IjUxMnB0IiB2aWV3Qm94PSIwIDAgNTEyIDUxMi4wMTA2NyIgd2lkdGg9IjUxMnB0IiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciPjxwYXRoIGQ9Im00MTAuNjcxODc1IDUxMi4wMTE3MTloLTg1LjMzMjAzMWMtOC44MzIwMzIgMC0xNi03LjE2Nzk2OS0xNi0xNnYtMTM4LjY2Nzk2OWMwLTIuOTQ1MzEyLTIuMzkwNjI1LTUuMzMyMDMxLTUuMzM1OTM4LTUuMzMyMDMxaC05NmMtMi45NDE0MDYgMC01LjMzMjAzMSAyLjM4NjcxOS01LjMzMjAzMSA1LjMzMjAzMXYxMzguNjY3OTY5YzAgOC44MzIwMzEtNy4xNjc5NjkgMTYtMTYgMTZoLTg1LjMzMjAzMWMtMjAuNTg1OTM4IDAtMzcuMzM1OTM4LTE2Ljc0NjA5NC0zNy4zMzU5MzgtMzcuMzM1OTM4di0xOTcuMzMyMDMxaC0zNy4zMzIwMzFjLTE0LjY5OTIxOSAwLTI2LjY2Nzk2ODc1LTExLjk2ODc1LTI2LjY2Nzk2ODc1LTI2LjY2Nzk2OSAwLTcuMDU4NTkzIDIuODgyODEyNzUtMTMuOTcyNjU2IDcuODk0NTMxNzUtMTguOTg0Mzc1bDIzNy4wMzUxNTYtMjI3LjI0MjE4N2M2LjE4NzUtNS45MzM1OTQgMTUuOTU3MDMxLTUuOTMzNTk0IDIyLjE0NDUzMSAwbDIzNi44MDA3ODEgMjI2Ljk4NDM3NWM1LjI0NjA5NCA1LjI2OTUzMSA4LjEyNSAxMi4xODM1OTQgOC4xMjUgMTkuMjQyMTg3IDAgMTQuNjk5MjE5LTExLjk2NDg0NCAyNi42Njc5NjktMjYuNjY0MDYyIDI2LjY2Nzk2OWgtMzcuMzM1OTM4djE5Ny4zMzIwMzFjMCAyMC41ODk4NDQtMTYuNzQ2MDk0IDM3LjMzNTkzOC0zNy4zMzIwMzEgMzcuMzM1OTM4em0tNjkuMzMyMDMxLTMyaDY5LjMzMjAzMWMyLjkwMjM0NCAwIDUuMzMyMDMxLTIuNDMzNTk0IDUuMzMyMDMxLTUuMzM1OTM4di0yMTMuMzMyMDMxYzAtOC44MzIwMzEgNy4xNjc5NjktMTYgMTYtMTZoNDAuMTI4OTA2bC0yMTYuMTI4OTA2LTIwNy4xNjc5NjktMjE2LjEyNSAyMDcuMTY3OTY5aDQwLjEyNWM4LjgzMjAzMiAwIDE2IDcuMTY3OTY5IDE2IDE2djIxMy4zMzIwMzFjMCAyLjkwMjM0NCAyLjQzMzU5NCA1LjMzNTkzOCA1LjMzNTkzOCA1LjMzNTkzOGg2OS4zMzIwMzF2LTEyMi42Njc5NjljMC0yMC41ODU5MzggMTYuNzQ2MDk0LTM3LjMzMjAzMSAzNy4zMzIwMzEtMzcuMzMyMDMxaDk2YzIwLjU4OTg0NCAwIDM3LjMzNTkzOCAxNi43NDYwOTMgMzcuMzM1OTM4IDM3LjMzMjAzMXptMCAwIi8+PC9zdmc+" style="width:2rem;">
    </a>
    <!-- device -->
    <a href="configDevice">
      <img src="data:image/svg+xml;utf8;base64,PD94bWwgdmVyc2lvbj0iMS4wIiBlbmNvZGluZz0iaXNvLTg4NTktMSI/Pg0KPCEtLSBHZW5lcmF0b3I6IEFkb2JlIElsbHVzdHJhdG9yIDE5LjEuMCwgU1ZHIEV4cG9ydCBQbHVnLUluIC4gU1ZHIFZlcnNpb246IDYuMDAgQnVpbGQgMCkgIC0tPg0KPHN2ZyB2ZXJzaW9uPSIxLjEiIGlkPSJDYXBhXzEiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgeG1sbnM6eGxpbms9Imh0dHA6Ly93d3cudzMub3JnLzE5OTkveGxpbmsiIHg9IjBweCIgeT0iMHB4Ig0KCSB2aWV3Qm94PSIwIDAgNDc4LjcwMyA0NzguNzAzIiBzdHlsZT0iZW5hYmxlLWJhY2tncm91bmQ6bmV3IDAgMCA0NzguNzAzIDQ3OC43MDM7IiB4bWw6c3BhY2U9InByZXNlcnZlIj4NCjxnPg0KCTxnPg0KCQk8cGF0aCBkPSJNNDU0LjIsMTg5LjEwMWwtMzMuNi01LjdjLTMuNS0xMS4zLTgtMjIuMi0xMy41LTMyLjZsMTkuOC0yNy43YzguNC0xMS44LDcuMS0yNy45LTMuMi0zOC4xbC0yOS44LTI5LjgNCgkJCWMtNS42LTUuNi0xMy04LjctMjAuOS04LjdjLTYuMiwwLTEyLjEsMS45LTE3LjEsNS41bC0yNy44LDE5LjhjLTEwLjgtNS43LTIyLjEtMTAuNC0zMy44LTEzLjlsLTUuNi0zMy4yDQoJCQljLTIuNC0xNC4zLTE0LjctMjQuNy0yOS4yLTI0LjdoLTQyLjFjLTE0LjUsMC0yNi44LDEwLjQtMjkuMiwyNC43bC01LjgsMzRjLTExLjIsMy41LTIyLjEsOC4xLTMyLjUsMTMuN2wtMjcuNS0xOS44DQoJCQljLTUtMy42LTExLTUuNS0xNy4yLTUuNWMtNy45LDAtMTUuNCwzLjEtMjAuOSw4LjdsLTI5LjksMjkuOGMtMTAuMiwxMC4yLTExLjYsMjYuMy0zLjIsMzguMWwyMCwyOC4xDQoJCQljLTUuNSwxMC41LTkuOSwyMS40LTEzLjMsMzIuN2wtMzMuMiw1LjZjLTE0LjMsMi40LTI0LjcsMTQuNy0yNC43LDI5LjJ2NDIuMWMwLDE0LjUsMTAuNCwyNi44LDI0LjcsMjkuMmwzNCw1LjgNCgkJCWMzLjUsMTEuMiw4LjEsMjIuMSwxMy43LDMyLjVsLTE5LjcsMjcuNGMtOC40LDExLjgtNy4xLDI3LjksMy4yLDM4LjFsMjkuOCwyOS44YzUuNiw1LjYsMTMsOC43LDIwLjksOC43YzYuMiwwLDEyLjEtMS45LDE3LjEtNS41DQoJCQlsMjguMS0yMGMxMC4xLDUuMywyMC43LDkuNiwzMS42LDEzbDUuNiwzMy42YzIuNCwxNC4zLDE0LjcsMjQuNywyOS4yLDI0LjdoNDIuMmMxNC41LDAsMjYuOC0xMC40LDI5LjItMjQuN2w1LjctMzMuNg0KCQkJYzExLjMtMy41LDIyLjItOCwzMi42LTEzLjVsMjcuNywxOS44YzUsMy42LDExLDUuNSwxNy4yLDUuNWwwLDBjNy45LDAsMTUuMy0zLjEsMjAuOS04LjdsMjkuOC0yOS44YzEwLjItMTAuMiwxMS42LTI2LjMsMy4yLTM4LjENCgkJCWwtMTkuOC0yNy44YzUuNS0xMC41LDEwLjEtMjEuNCwxMy41LTMyLjZsMzMuNi01LjZjMTQuMy0yLjQsMjQuNy0xNC43LDI0LjctMjkuMnYtNDIuMQ0KCQkJQzQ3OC45LDIwMy44MDEsNDY4LjUsMTkxLjUwMSw0NTQuMiwxODkuMTAxeiBNNDUxLjksMjYwLjQwMWMwLDEuMy0wLjksMi40LTIuMiwyLjZsLTQyLDdjLTUuMywwLjktOS41LDQuOC0xMC44LDkuOQ0KCQkJYy0zLjgsMTQuNy05LjYsMjguOC0xNy40LDQxLjljLTIuNyw0LjYtMi41LDEwLjMsMC42LDE0LjdsMjQuNywzNC44YzAuNywxLDAuNiwyLjUtMC4zLDMuNGwtMjkuOCwyOS44Yy0wLjcsMC43LTEuNCwwLjgtMS45LDAuOA0KCQkJYy0wLjYsMC0xLjEtMC4yLTEuNS0wLjVsLTM0LjctMjQuN2MtNC4zLTMuMS0xMC4xLTMuMy0xNC43LTAuNmMtMTMuMSw3LjgtMjcuMiwxMy42LTQxLjksMTcuNGMtNS4yLDEuMy05LjEsNS42LTkuOSwxMC44bC03LjEsNDINCgkJCWMtMC4yLDEuMy0xLjMsMi4yLTIuNiwyLjJoLTQyLjFjLTEuMywwLTIuNC0wLjktMi42LTIuMmwtNy00MmMtMC45LTUuMy00LjgtOS41LTkuOS0xMC44Yy0xNC4zLTMuNy0yOC4xLTkuNC00MS0xNi44DQoJCQljLTIuMS0xLjItNC41LTEuOC02LjgtMS44Yy0yLjcsMC01LjUsMC44LTcuOCwyLjVsLTM1LDI0LjljLTAuNSwwLjMtMSwwLjUtMS41LDAuNWMtMC40LDAtMS4yLTAuMS0xLjktMC44bC0yOS44LTI5LjgNCgkJCWMtMC45LTAuOS0xLTIuMy0wLjMtMy40bDI0LjYtMzQuNWMzLjEtNC40LDMuMy0xMC4yLDAuNi0xNC44Yy03LjgtMTMtMTMuOC0yNy4xLTE3LjYtNDEuOGMtMS40LTUuMS01LjYtOS0xMC44LTkuOWwtNDIuMy03LjINCgkJCWMtMS4zLTAuMi0yLjItMS4zLTIuMi0yLjZ2LTQyLjFjMC0xLjMsMC45LTIuNCwyLjItMi42bDQxLjctN2M1LjMtMC45LDkuNi00LjgsMTAuOS0xMGMzLjctMTQuNyw5LjQtMjguOSwxNy4xLTQyDQoJCQljMi43LTQuNiwyLjQtMTAuMy0wLjctMTQuNmwtMjQuOS0zNWMtMC43LTEtMC42LTIuNSwwLjMtMy40bDI5LjgtMjkuOGMwLjctMC43LDEuNC0wLjgsMS45LTAuOGMwLjYsMCwxLjEsMC4yLDEuNSwwLjVsMzQuNSwyNC42DQoJCQljNC40LDMuMSwxMC4yLDMuMywxNC44LDAuNmMxMy03LjgsMjcuMS0xMy44LDQxLjgtMTcuNmM1LjEtMS40LDktNS42LDkuOS0xMC44bDcuMi00Mi4zYzAuMi0xLjMsMS4zLTIuMiwyLjYtMi4yaDQyLjENCgkJCWMxLjMsMCwyLjQsMC45LDIuNiwyLjJsNyw0MS43YzAuOSw1LjMsNC44LDkuNiwxMCwxMC45YzE1LjEsMy44LDI5LjUsOS43LDQyLjksMTcuNmM0LjYsMi43LDEwLjMsMi41LDE0LjctMC42bDM0LjUtMjQuOA0KCQkJYzAuNS0wLjMsMS0wLjUsMS41LTAuNWMwLjQsMCwxLjIsMC4xLDEuOSwwLjhsMjkuOCwyOS44YzAuOSwwLjksMSwyLjMsMC4zLDMuNGwtMjQuNywzNC43Yy0zLjEsNC4zLTMuMywxMC4xLTAuNiwxNC43DQoJCQljNy44LDEzLjEsMTMuNiwyNy4yLDE3LjQsNDEuOWMxLjMsNS4yLDUuNiw5LjEsMTAuOCw5LjlsNDIsNy4xYzEuMywwLjIsMi4yLDEuMywyLjIsMi42djQyLjFINDUxLjl6Ii8+DQoJCTxwYXRoIGQ9Ik0yMzkuNCwxMzYuMDAxYy01NywwLTEwMy4zLDQ2LjMtMTAzLjMsMTAzLjNzNDYuMywxMDMuMywxMDMuMywxMDMuM3MxMDMuMy00Ni4zLDEwMy4zLTEwMy4zUzI5Ni40LDEzNi4wMDEsMjM5LjQsMTM2LjAwMQ0KCQkJeiBNMjM5LjQsMzE1LjYwMWMtNDIuMSwwLTc2LjMtMzQuMi03Ni4zLTc2LjNzMzQuMi03Ni4zLDc2LjMtNzYuM3M3Ni4zLDM0LjIsNzYuMyw3Ni4zUzI4MS41LDMxNS42MDEsMjM5LjQsMzE1LjYwMXoiLz4NCgk8L2c+DQo8L2c+DQo8Zz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8Zz4NCjwvZz4NCjxnPg0KPC9nPg0KPGc+DQo8L2c+DQo8L3N2Zz4NCg==" style="width:2rem;">
    </a>
  </div>
</body>
<script>
  function saveStatus() {
    var mqtt_status;
    var xhr = new XMLHttpRequest();
    if (document.getElementById('check').checked) {
      mqtt_status = '1';
    } else {
      mqtt_status = '0';
    }
    xhr.open("POST", '/saveStatus?mqtt_status=' + mqtt_status);
    xhr.send();
    alert('Changes will be applied after reboot.');
  }

  function saveConfig() {
    var xhr = new XMLHttpRequest();
    var params = 'mqtt_server=' + mqtt_server.value + '&mqtt_port=' + mqtt_port.value + '&mqtt_user=' + mqtt_user.value + '&mqtt_password=' + mqtt_password.value;
    xhr.open("POST", '/saveConfig?' + params);
    xhr.send();
    alert('Changes will be applied after reboot.');
  }

  function loadConfig() {
    var xhr = new XMLHttpRequest();
    xhr.open("POST", '/loadConfig');
    xhr.send(null);
    xhr.onload = function() {
      if (xhr.status == 200) {
        var json = JSON.parse(xhr.response);
        if (json.mqtt_status == "1") {
          document.getElementById('check').checked = true;
        }
        document.getElementById('mqtt_server').value = json.mqtt_server;
        document.getElementById('mqtt_port').value = json.mqtt_port;
        document.getElementById('mqtt_user').value = json.mqtt_user;
        document.getElementById('mqtt_password').value = '********';
      }
    };
  }
</script>

</html>
)=====";
