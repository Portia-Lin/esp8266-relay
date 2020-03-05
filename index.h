const char INDEX_PAGE[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
  <meta name='viewport' content='width=device-width, initial-scale=1.0' />
  <meta charset='utf-8'>
</head>
<style>
  body {
    background-color: #F7F9FD;
  }

  .container {
    width: 20rem;
    margin-left: auto;
    margin-right: auto;
    text-align: center;
  }

  button {
    display: block;
    width: 10rem;
    height: 10rem;
    border: none;
    border-radius: 25%;
    margin-left: auto;
    margin-right: auto;
    background-color: #DBE1EA;
    outline: none;
  }

  a {
    float: right;
    outline: none;
    text-decoration: none;
    margin-left: 1rem;

  }

  a img { border: none; }

  a:hover {
    text-decoration: none;
    outline: none;

  }

  button:active {
    background-color: #E9E9E6;
  }
  
  #circl {
    transition: stroke 1s ease;
  }

</style>

<body>
  <div class="container">
    <h1 class="center">TEST PAGE</h1>
    <h1 class="center" id="state">---</h1> <br> <br>
    <button type="button" id="switch">
      <svg width="9rem" height="9rem">
        <circle id="circl" r="4rem" cx="4.5rem" cy="4.5rem" fill="none" stroke="#000000" stroke-width="0.2rem" />
      </svg>
    </button> <br> <br>
    <p class="center">Recieved data = <span id='rd'>---</span></p><br>
    <a href="#">
      <img src="data:image/svg+xml;utf8;base64,PHN2ZyBoZWlnaHQ9IjUxMiIgdmlld0JveD0iMCAwIDY0IDY0IiB3aWR0aD0iNTEyIiB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciPjxnIGlkPSJSb3V0ZXIiPjxwYXRoIGQ9Im01OSAyNS43NzFoLTI4LjIzYTUuMDA2IDUuMDA2IDAgMCAwIC01IDV2MjguMjI5YTUuMDA2IDUuMDA2IDAgMCAwIDUgNWgyOC4yM2E1LjAwNiA1LjAwNiAwIDAgMCA1LTV2LTI4LjIyOWE1LjAwNiA1LjAwNiAwIDAgMCAtNS01em0tMTAuNjMzIDI2LjFhMSAxIDAgMCAxIC0xLjQxNCAwIDIuOTI4IDIuOTI4IDAgMCAwIC00LjEzNiAwIDEgMSAwIDAgMSAtMS40MTctMS40MSA0LjkzMiA0LjkzMiAwIDAgMSA2Ljk2NCAwIDEgMSAwIDAgMSAuMDAzIDEuNDE1em00LjAzOS00LjA0YTEgMSAwIDAgMSAtMS40MTQgMCA4LjY0NyA4LjY0NyAwIDAgMCAtMTIuMjE0IDAgMSAxIDAgMCAxIC0xLjQxNC0xLjQxNCAxMC42NDkgMTAuNjQ5IDAgMCAxIDE1LjA0MiAwIDEgMSAwIDAgMSAwIDEuNDE5em00LjAzOS00LjAzMWExIDEgMCAwIDEgLTEuNDE0IDAgMTQuMzY2IDE0LjM2NiAwIDAgMCAtMjAuMjkyIDAgMSAxIDAgMSAxIC0xLjQxNC0xLjQxNCAxNi4zNjYgMTYuMzY2IDAgMCAxIDIzLjEyIDAgMSAxIDAgMCAxIDAgMS40MTR6IiBmaWxsPSIjYzRhMmZjIi8+PGcgZmlsbD0iIzE1MWE2YSI+PHBhdGggZD0ibTQ2LjUgMjAuNmgtMzIuNTE1di0xLjkyN2EyIDIgMCAwIDAgLTEuNDExLTEuOXYtMTMuODJhMi45NTMgMi45NTMgMCAxIDAgLTUuOSAwdjEzLjgxOWEyIDIgMCAwIDAgLTEuNDEyIDEuOXYxLjkyOGgtMy4yNjJhMiAyIDAgMCAwIC0yIDJ2MTEuMTVhMiAyIDAgMCAwIDEuOTQgMS45OTR2LjlhMyAzIDAgMCAwIDMgM2gzLjgxMWEzIDMgMCAwIDAgMy0zdi0uODk0aDI0LjkzOXYuODkxYTMgMyAwIDAgMCAzIDNoMy44MWEzIDMgMCAwIDAgMy0zdi0uODkxYTIgMiAwIDAgMCAyLTJ2LTExLjE1YTIgMiAwIDAgMCAtMi0yem0tMzcuODMxLTE3LjY0N2EuOTUzLjk1MyAwIDEgMSAxLjkgMHYxMy43MmgtMS45em0tMS40MTIgMTUuNzJoNC43Mjh2MS45MjdoLTQuNzI4em0yLjQ5NCAxNy45NjhhMSAxIDAgMCAxIC0xIDFoLTMuODExYTEgMSAwIDAgMSAtMS0xdi0uODkxaDUuODExem0zNC43NDkgMGExIDEgMCAwIDEgLTEgMWgtMy44MWExIDEgMCAwIDEgLTEtMXYtLjg5MWg1Ljgxem0tNDIuNS0yLjg5MXYtMTEuMTVoNDQuNXYxMS4xNTN6Ii8+PHBhdGggZD0ibTguMSAyNS4xYTMuMDc1IDMuMDc1IDAgMSAwIDMuMDc0IDMuMDc0IDMuMDc4IDMuMDc4IDAgMCAwIC0zLjA3NC0zLjA3NHptMCA0LjE0OWExLjA3NSAxLjA3NSAwIDEgMSAxLjA3NC0xLjA3NSAxLjA3NiAxLjA3NiAwIDAgMSAtMS4wNzQgMS4wNzR6Ii8+PHBhdGggZD0ibTE2LjA4NyAyNC44NTJhMy4wNzQgMy4wNzQgMCAxIDAgMy4wNzUgMy4wNzQgMy4wNzcgMy4wNzcgMCAwIDAgLTMuMDc1LTMuMDc0em0wIDQuMTQ4YTEuMDc0IDEuMDc0IDAgMSAxIDEuMDc1LTEuMDc0IDEuMDc1IDEuMDc1IDAgMCAxIC0xLjA3NSAxLjA3NHoiLz48cGF0aCBkPSJtNDEuNiAyNi45MjZoLTEwLjQxN2ExIDEgMCAwIDAgMCAyaDEwLjQxN2ExIDEgMCAwIDAgMC0yeiIvPjwvZz48L2c+PC9zdmc+" style="width:2.5rem;">
    </a>
    <a href="config">
      <img src="data:image/svg+xml;utf8;base64,PHN2ZyBpZD0iTGF5ZXJfMiIgaGVpZ2h0PSI1MTIiIHZpZXdCb3g9IjAgMCA2NCA2NCIgd2lkdGg9IjUxMiIgeG1sbnM9Imh0dHA6Ly93d3cudzMub3JnLzIwMDAvc3ZnIiBkYXRhLW5hbWU9IkxheWVyIDIiPjxnIGZpbGw9IiNjNGEyZmMiPjxwYXRoIGQ9Im0zMiAxMC41YTUxLjUwNyA1MS41MDcgMCAwIDEgOC4yNzguNjUxYy0xLjMwMi01LjQ1MS0zLjUzNS05LjU2My02LjE0NS0xMS4wNDYtLjcwMi0uMDY4LTEuNDEzLS4xMDUtMi4xMzMtLjEwNXMtMS40MzEuMDM3LTIuMTMzLjEwNWMtMi42MSAxLjQ4My00Ljg0MyA1LjYtNi4xNDUgMTEuMDQ2YTUxLjUwNyA1MS41MDcgMCAwIDEgOC4yNzgtLjY1MXoiLz48cGF0aCBkPSJtMzIgMzMuNWE1MS41MDcgNTEuNTA3IDAgMCAxIC04LjI3OC0uNjUxYzEuMyA1LjQ0NyAzLjUzNSA5LjU2MyA2LjE0NSAxMS4wNDYuNy4wNjggMS40MTMuMSAyLjEzMy4xczEuNDMxLS4wMzcgMi4xMzMtLjFjMi42MS0xLjQ4MyA0Ljg0My01LjYgNi4xNDUtMTEuMDQ2YTUxLjUwNyA1MS41MDcgMCAwIDEgLTguMjc4LjY1MXoiLz48cGF0aCBkPSJtNDAuNzI3IDEzLjI3M2E0OS42NDkgNDkuNjQ5IDAgMCAwIC0xNy40NTQgMCA0OS42NDkgNDkuNjQ5IDAgMCAwIDAgMTcuNDU0IDQ4LjYgNDguNiAwIDAgMCA4LjcyNy43NzMgNDguNiA0OC42IDAgMCAwIDguNzI3LS43NzMgNDguNiA0OC42IDAgMCAwIC43NzMtOC43MjcgNDguNiA0OC42IDAgMCAwIC0uNzczLTguNzI3eiIvPjxwYXRoIGQ9Im01My45IDI0LjEzM2MuMDY4LS43LjEtMS40MTMuMS0yLjEzM3MtLjAzNy0xLjQzMS0uMS0yLjEzM2MtMS40ODMtMi42MS01LjYtNC44NDMtMTEuMDQ2LTYuMTQ1YTUxLjUwNyA1MS41MDcgMCAwIDEgLjY0NiA4LjI3OCA1MS41MDcgNTEuNTA3IDAgMCAxIC0uNjUxIDguMjc4YzUuNDUxLTEuMzAyIDkuNTYzLTMuNTM1IDExLjA1MS02LjE0NXoiLz48cGF0aCBkPSJtMjEuMTUxIDMwLjI3OGE1MS41MDcgNTEuNTA3IDAgMCAxIC0uNjUxLTguMjc4IDUxLjUwNyA1MS41MDcgMCAwIDEgLjY1MS04LjI3OGMtNS40NDcgMS4zLTkuNTYzIDMuNTM1LTExLjA0NiA2LjE0NS0uMDY4LjcwMi0uMTA1IDEuNDEzLS4xMDUgMi4xMzNzLjAzNyAxLjQzMS4xMDUgMi4xMzNjMS40ODMgMi42MSA1LjU5NSA0Ljg0MyAxMS4wNDYgNi4xNDV6Ii8+PHBhdGggZD0ibTQyLjQzOSAzMi40MzlhMjYuMDUyIDI2LjA1MiAwIDAgMSAtNC42IDEwLjc2OSAyMi4wNzcgMjIuMDc3IDAgMCAwIDE1LjM2OS0xNS4zNzMgMjYuMDUyIDI2LjA1MiAwIDAgMSAtMTAuNzY5IDQuNjA0eiIvPjxwYXRoIGQ9Im0yMS41NjEgMzIuNDM5YTI2LjA1MiAyNi4wNTIgMCAwIDEgLTEwLjc2OS00LjYgMjIuMDc3IDIyLjA3NyAwIDAgMCAxNS4zNzMgMTUuMzY5IDI2LjA1MiAyNi4wNTIgMCAwIDEgLTQuNjA0LTEwLjc2OXoiLz48cGF0aCBkPSJtMjEuNTYxIDExLjU2MWEyNi4wNTIgMjYuMDUyIDAgMCAxIDQuNjA0LTEwLjc2OSAyMi4wNzcgMjIuMDc3IDAgMCAwIC0xNS4zNzMgMTUuMzczIDI2LjA1MiAyNi4wNTIgMCAwIDEgMTAuNzY5LTQuNjA0eiIvPjxwYXRoIGQ9Im00Mi40MzkgMTEuNTYxYTI2LjA1MiAyNi4wNTIgMCAwIDEgMTAuNzY5IDQuNiAyMi4wNzcgMjIuMDc3IDAgMCAwIC0xNS4zNzMtMTUuMzY5IDI2LjA1MiAyNi4wNTIgMCAwIDEgNC42MDQgMTAuNzY5eiIvPjwvZz48cGF0aCBkPSJtNTkgNDhoLTIzLjA2NGwtMS45MzYtMjkuMDY2YTEgMSAwIDAgMCAtMS0uOTM0aC0yYTEgMSAwIDAgMCAtMSAuOTM0bC0xLjkzNiAyOS4wNjZoLTIzLjA2NGE1LjAwNiA1LjAwNiAwIDAgMCAtNSA1djZhNS4wMDYgNS4wMDYgMCAwIDAgNSA1aDU0YTUuMDA2IDUuMDA2IDAgMCAwIDUtNXYtNmE1LjAwNiA1LjAwNiAwIDAgMCAtNS01em0tMjcuMDY0LTI4aC4xMjhsMS44NjcgMjhoLTMuODYyem0xMi4wNjQgNDJoLTM5YTMgMyAwIDAgMSAtMy0zdi02YTMgMyAwIDAgMSAzLTNoMzl6bTYgMGgtNHYtMTJoNHptNiAwaC00di0xMmg0em02LTNhMyAzIDAgMCAxIC0zIDNoLTF2LTEyaDFhMyAzIDAgMCAxIDMgM3oiIGZpbGw9IiMxNTFhNmEiLz48Y2lyY2xlIGN4PSI4IiBjeT0iNTYiIGZpbGw9IiMxNTFhNmEiIHI9IjEiLz48cGF0aCBkPSJtMjIuMSAxMi4xYTE0LjAxNCAxNC4wMTQgMCAwIDEgMTkuOCAwIDEgMSAwIDAgMCAxLjQxNC0xLjQxNCAxNi4wMTUgMTYuMDE1IDAgMCAwIC0yMi42MjYgMCAxIDEgMCAxIDAgMS40MTIgMS40MTR6IiBmaWxsPSIjMTUxYTZhIi8+PHBhdGggZD0ibTI0LjkyOSAxNC45MjlhMSAxIDAgMCAwIDEuNDE0IDEuNDE0IDguMDEgOC4wMSAwIDAgMSAxMS4zMTQgMCAxIDEgMCAwIDAgMS40MTQtMS40MTQgMTAuMDExIDEwLjAxMSAwIDAgMCAtMTQuMTQyIDB6IiBmaWxsPSIjMTUxYTZhIi8+PC9zdmc+" style="width:2.5rem;">
    </a>
  </div>
</body>
<script>
  var Socket;

  function init() {
    Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
    Socket.onmessage = function(event) { processReceivedCommand(event); };
  }


  function processReceivedCommand(evt) {
    document.getElementById('rd').innerHTML = evt.data;
    if (evt.data === '0') {
      document.getElementById('state').innerHTML = 'O F F';
      document.getElementById('circl').style.stroke = '#F583AE';
    }
    if (evt.data === '1') {
      document.getElementById('state').innerHTML = 'O N';
      document.getElementById('circl').style.stroke = '#2BAAFF';
    }
  }


  document.getElementById('switch').addEventListener('click', buttonToggle);

  function buttonToggle() {
    var btn = document.getElementById('switch')
    sendText('t');
}

function sendText(data) {
    Socket.send(data);
}


window.onload = function(e) {
    init();
}
</script>

</html>
)=====";
