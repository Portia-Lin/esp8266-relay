const char CONFIG_PAGE[] PROGMEM = R"=====(
<!DOCTYPE html>

<head>
  <title>Configure MQTT</title>
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
    }

    .m_left {
      margin-left: 1rem;
    }

    input[type=text] {
      width: 18rem;
      border: 0.05rem solid #DA5868;
      border-radius: 0.5rem;
      padding: 0.7rem 1rem;
    }

    input[type=text]:focus {
      border: 0.05rem dashed #CD3341;
      outline:none;
    }

    .checkbox {
      position:relative;
      padding-left:25px;
    }
    .checkbox input[type=checkbox] {
      display:none;
    }

    .checkbox label:after {
      content:'';
      display:block;
      height:14px;
      width:14px;
      outline:1px solid #939598;
      position:absolute;
      top:0;
      left:0;
    }

    .checkbox input[type=checkbox]:checked + label:after {
      outline:1px solid #939598;
      border:2px solid #fff;
      width:10px;
      height:10px;
      background-color:#63849F;
    }

    input[type=button] {
      display: block;
      width: 80%;
      padding: 1rem 0rem;
      border: none;
      border-radius: 0.5rem;
      background-color: #DA5868;
      font-family: 'Montserrat', sans-serif;
      font-size: 11pt;
      letter-spacing: 0.05rem;
      text-align: center;
      font-weight: bold;
      text-decoration: none;
      outline: none;
      color: white;
      margin-left: auto;
      margin-right: auto;
    }

    input[type=button]:active {
      background-color: #CD3341;
    }

    a {
      float: right;
      outline: none;
      text-decoration: none;
      margin-left: 1rem;
    }

    .center {
      text-align: center;
    }
  </style>
</head>

<body onload="loadConfig();">
  <div class="container m_bottom">
    <h2 class="center"><b>MQTT Client properties</b></h2><br>
    <div class="checkbox m_left">
      <input onclick="saveStatus();" type="checkbox" id="check"><label for="check">Enable MQTT connection</label>
    </div>
    <p class="m_left">MQTT Server:</p>
    <input type="text" id="mqtt_server" placeholder="mqtt server">
    <p class="m_left">MQTT Port:</p>
    <input type="text" id="mqtt_port" placeholder="mqtt port">
    <p class="m_left">MQTT User:</p>
    <input type="text" id="mqtt_user" placeholder="mqtt user">
    <p class="m_left">MQTT Password:</p>
    <input type="text" id="mqtt_password" placeholder="mqtt password">
    <br><br><br>
    <input onclick="saveConfig();" type="button" id="sendbtn" value="SUBMIT">
    <br><br>
    <a href="/">
      <img src="data:image/svg+xml;utf8;base64,PHN2ZyBpZD0iTGF5ZXJfMiIgaGVpZ2h0PSI1MTIiIHZpZXdCb3g9IjAgMCA2NCA2NCIgd2lkdGg9IjUxMiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiBkYXRhLW5hbWU9IkxheWVyIDIiPjxwYXRoIGQ9Im0zOC4xMzUgMjYuNjl2LjkzNmExIDEgMCAwIDEgLTEgMSAxLjY1IDEuNjUgMCAwIDAgLTEuNDU2Ljg3MWwtLjMzNS42MjdhMy42NDggMy42NDggMCAwIDEgLTMuMjE5IDEuOTI2aC0uMjVhMy42NDUgMy42NDUgMCAwIDEgLTMuMjE4LTEuOTI2bC0uMzM3LS42MjRhMS42NDcgMS42NDcgMCAwIDAgLTEuNDU1LS44NzEgMSAxIDAgMCAxIC0xLTF2LS45MzlhNC45OSA0Ljk5IDAgMCAwIC00LjM2NSA0LjkzNnYyNy4zNzRhNS4wMDYgNS4wMDYgMCAwIDAgNSA1aDExYTUuMDA2IDUuMDA2IDAgMCAwIDUtNXYtMjcuMzc0YTQuOTkgNC45OSAwIDAgMCAtNC4zNjUtNC45MzZ6IiBmaWxsPSIjYzRhMmZjIi8+PHBhdGggZD0ibTMwLjA4MyAyOC41NTIuMzM3LjYyN2ExLjY0OSAxLjY0OSAwIDAgMCAxLjQ1NS44NzFoLjI1YTEuNjUyIDEuNjUyIDAgMCAwIDEuNDU2LS44NzFsLjMzNS0uNjI3YTMuNjQ3IDMuNjQ3IDAgMCAxIDIuMjE5LTEuNzg3di0uMTM5aC04LjI3di4xMzlhMy42NDUgMy42NDUgMCAwIDEgMi4yMTggMS43ODd6IiBmaWxsPSIjYzRhMmZjIi8+PGcgZmlsbD0iIzE1MWE2YSI+PHBhdGggZD0ibTI3IDM2LjUzNGgtOWEzIDMgMCAwIDAgLTMgM3Y5YTMgMyAwIDAgMCAzIDNoOWEzIDMgMCAwIDAgMy0zdi05YTMgMyAwIDAgMCAtMy0zem0tNS41IDEzaC0zLjVhMSAxIDAgMCAxIC0xLTF2LTMuNWg0LjV6bTAtNi41aC00LjV2LTMuNWExIDEgMCAwIDEgMS0xaDMuNXptNi41IDUuNWExIDEgMCAwIDEgLTEgMWgtMy41di00LjVoNC41em0wLTUuNWgtNC41di00LjVoMy41YTEgMSAwIDAgMSAxIDF6Ii8+PHBhdGggZD0ibTIwLjY4NiAxNi42ODZhMSAxIDAgMCAwIDEuNDE0IDEuNDE0IDE0LjAxNSAxNC4wMTUgMCAwIDEgMTkuOCAwIDEgMSAwIDAgMCAxLjQxNC0xLjQxNCAxNi4wMTggMTYuMDE4IDAgMCAwIC0yMi42MjggMHoiLz48cGF0aCBkPSJtMzkuMDcxIDIyLjM0MmExIDEgMCAwIDAgMC0xLjQxNCAxMC4wMTMgMTAuMDEzIDAgMCAwIC0xNC4xNDIgMCAxIDEgMCAwIDAgMS40MTQgMS40MTQgOC4wMSA4LjAxIDAgMCAxIDExLjMxNCAwIDEgMSAwIDAgMCAxLjQxNCAweiIvPjxwYXRoIGQ9Im02My42NTEgMjUuNTcyLTguNjUxLTcuNDIxdi0xMS4xNDJhMSAxIDAgMCAwIC0xLTFoLTZhMSAxIDAgMCAwIC0xIDF2NC4yNzlsLTExLjc0NC0xMC4wNzRhNC45NzMgNC45NzMgMCAwIDAgLTYuNTEyIDBsLTI4LjM5NSAyNC4zNThhMSAxIDAgMCAwIC42NTEgMS43NTloOHYyNS42NzhhNS4wMDYgNS4wMDYgMCAwIDAgNSA1aDM2YTUuMDA1IDUuMDA1IDAgMCAwIDUtNXYtMjUuNjc4aDhhMSAxIDAgMCAwIC42NTEtMS43NTl6bS0xNC42NTEtMTcuNTYzaDR2OC40MjZsLTQtMy40MzV6bTUgMTcuMzIyYTEgMSAwIDAgMCAtMSAxdjI2LjY3OGEzIDMgMCAwIDEgLTMgM2gtMzZhMyAzIDAgMCAxIC0zLTN2LTI2LjY3OGExIDEgMCAwIDAgLTEtMWgtNi4zbDI2LjM0NC0yMi42YTIuOTgzIDIuOTgzIDAgMCAxIDMuOTA2IDBsMjYuMzUgMjIuNnoiLz48cGF0aCBkPSJtMzQgMzkuNTM0djlhMyAzIDAgMCAwIDMgM2g5YTMgMyAwIDAgMCAzLTN2LTlhMyAzIDAgMCAwIC0zLTNoLTlhMyAzIDAgMCAwIC0zIDN6bTYuNSAxMGgtMy41YTEgMSAwIDAgMSAtMS0xdi0zLjVoNC41em0yLTExaDMuNWExIDEgMCAwIDEgMSAxdjMuNWgtNC41em0wIDYuNWg0LjV2My41YTEgMSAwIDAgMSAtMSAxaC0zLjV6bS0yLTJoLTQuNXYtMy41YTEgMSAwIDAgMSAxLTFoMy41eiIvPjwvZz48L3N2Zz4=" style="width:2.5rem;">
    </a>
    <a href="#">
      <img src="data:image/svg+xml;utf8;base64,PHN2ZyBoZWlnaHQ9IjUxMiIgdmlld0JveD0iMCAwIDY0IDY0IiB3aWR0aD0iNTEyIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciPjxnIGlkPSJSb3V0ZXIiPjxwYXRoIGQ9Im01OSAyNS43NzFoLTI4LjIzYTUuMDA2IDUuMDA2IDAgMCAwIC01IDV2MjguMjI5YTUuMDA2IDUuMDA2IDAgMCAwIDUgNWgyOC4yM2E1LjAwNiA1LjAwNiAwIDAgMCA1LTV2LTI4LjIyOWE1LjAwNiA1LjAwNiAwIDAgMCAtNS01em0tMTAuNjMzIDI2LjFhMSAxIDAgMCAxIC0xLjQxNCAwIDIuOTI4IDIuOTI4IDAgMCAwIC00LjEzNiAwIDEgMSAwIDAgMSAtMS40MTctMS40MSA0LjkzMiA0LjkzMiAwIDAgMSA2Ljk2NCAwIDEgMSAwIDAgMSAuMDAzIDEuNDE1em00LjAzOS00LjA0YTEgMSAwIDAgMSAtMS40MTQgMCA4LjY0NyA4LjY0NyAwIDAgMCAtMTIuMjE0IDAgMSAxIDAgMCAxIC0xLjQxNC0xLjQxNCAxMC42NDkgMTAuNjQ5IDAgMCAxIDE1LjA0MiAwIDEgMSAwIDAgMSAwIDEuNDE5em00LjAzOS00LjAzMWExIDEgMCAwIDEgLTEuNDE0IDAgMTQuMzY2IDE0LjM2NiAwIDAgMCAtMjAuMjkyIDAgMSAxIDAgMSAxIC0xLjQxNC0xLjQxNCAxNi4zNjYgMTYuMzY2IDAgMCAxIDIzLjEyIDAgMSAxIDAgMCAxIDAgMS40MTR6IiBmaWxsPSIjYzRhMmZjIi8+PGcgZmlsbD0iIzE1MWE2YSI+PHBhdGggZD0ibTQ2LjUgMjAuNmgtMzIuNTE1di0xLjkyN2EyIDIgMCAwIDAgLTEuNDExLTEuOXYtMTMuODJhMi45NTMgMi45NTMgMCAxIDAgLTUuOSAwdjEzLjgxOWEyIDIgMCAwIDAgLTEuNDEyIDEuOXYxLjkyOGgtMy4yNjJhMiAyIDAgMCAwIC0yIDJ2MTEuMTVhMiAyIDAgMCAwIDEuOTQgMS45OTR2LjlhMyAzIDAgMCAwIDMgM2gzLjgxMWEzIDMgMCAwIDAgMy0zdi0uODk0aDI0LjkzOXYuODkxYTMgMyAwIDAgMCAzIDNoMy44MWEzIDMgMCAwIDAgMy0zdi0uODkxYTIgMiAwIDAgMCAyLTJ2LTExLjE1YTIgMiAwIDAgMCAtMi0yem0tMzcuODMxLTE3LjY0N2EuOTUzLjk1MyAwIDEgMSAxLjkgMHYxMy43MmgtMS45em0tMS40MTIgMTUuNzJoNC43Mjh2MS45MjdoLTQuNzI4em0yLjQ5NCAxNy45NjhhMSAxIDAgMCAxIC0xIDFoLTMuODExYTEgMSAwIDAgMSAtMS0xdi0uODkxaDUuODExem0zNC43NDkgMGExIDEgMCAwIDEgLTEgMWgtMy44MWExIDEgMCAwIDEgLTEtMXYtLjg5MWg1Ljgxem0tNDIuNS0yLjg5MXYtMTEuMTVoNDQuNXYxMS4xNTN6Ii8+PHBhdGggZD0ibTguMSAyNS4xYTMuMDc1IDMuMDc1IDAgMSAwIDMuMDc0IDMuMDc0IDMuMDc4IDMuMDc4IDAgMCAwIC0zLjA3NC0zLjA3NHptMCA0LjE0OWExLjA3NSAxLjA3NSAwIDEgMSAxLjA3NC0xLjA3NSAxLjA3NiAxLjA3NiAwIDAgMSAtMS4wNzQgMS4wNzR6Ii8+PHBhdGggZD0ibTE2LjA4NyAyNC44NTJhMy4wNzQgMy4wNzQgMCAxIDAgMy4wNzUgMy4wNzQgMy4wNzcgMy4wNzcgMCAwIDAgLTMuMDc1LTMuMDc0em0wIDQuMTQ4YTEuMDc0IDEuMDc0IDAgMSAxIDEuMDc1LTEuMDc0IDEuMDc1IDEuMDc1IDAgMCAxIC0xLjA3NSAxLjA3NHoiLz48cGF0aCBkPSJtNDEuNiAyNi45MjZoLTEwLjQxN2ExIDEgMCAwIDAgMCAyaDEwLjQxN2ExIDEgMCAwIDAgMC0yeiIvPjwvZz48L2c+PC9zdmc+" style="width:2.5rem;">
    </a><br>
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
