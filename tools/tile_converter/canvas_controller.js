original_canvas = null;
original_ctx = null;
tiles_canvas = null;
tiles_ctx = null;
palettes_canvas = null;
palettes_ctx = null;
unique_colors = new Array();

function init() {
  original_canvas = document.getElementById("png");
  original_canvas.width  = document.getElementById('png_holder').clientWidth;
  original_canvas.height = document.getElementById('png_holder').clientHeight;
  original_ctx = original_canvas.getContext('2d');
  original_ctx.fillStyle='black';
  original_ctx.scale(2,2);
  original_ctx.imageSmoothingEnabled = false;
  original_ctx.fillRect(0,0,original_canvas.width,original_canvas.height);

  tiles_canvas = document.getElementById("tiles");
  tiles_canvas.width  = document.getElementById('tiles_holder').clientWidth;
  tiles_canvas.height = document.getElementById('tiles_holder').clientHeight;
  tiles_ctx = tiles_canvas.getContext('2d');
  tiles_ctx.fillStyle='black';
  tiles_ctx.scale(2,2);
  tiles_ctx.imageSmoothingEnabled = false;
  tiles_ctx.fillRect(0,0,tiles_canvas.width,tiles_canvas.height);

  palettes_canvas = document.getElementById("palettes");
  palettes_canvas.width  = document.getElementById('palettes_holder').clientWidth;
  palettes_canvas.height = document.getElementById('palettes_holder').clientHeight;
  palettes_ctx = palettes_canvas.getContext('2d');
  palettes_ctx.fillStyle='black';
  palettes_ctx.imageSmoothingEnabled = false;
  palettes_ctx.fillRect(0,0,palettes_canvas.width,palettes_canvas.height);

  document.getElementById('image_file').onchange = function (evt) {
    var tgt = evt.target || window.event.srcElement,
        files = tgt.files;

    // FileReader support
    if (FileReader && files && files.length) {
        var fr = new FileReader();
        fr.onload = () => showImage(fr);
        fr.readAsDataURL(files[0]);

    }
  }
}

function showImage(fileReader) {
  var img = document.getElementById("hidden_image");
  img.onload = () => {
    getImageData(img);
    showTiles(img, 2);
    showPalettes(img);
  }
  img.src = fileReader.result;
}

function getImageData(img) {
  original_ctx.drawImage(img, 0, 0);
  imageData = original_ctx.getImageData(0, 0, img.width, img.height).data;

  for (var i = 0; i < imageData.length; i+=4) {
    var entry = [imageData[i], imageData[i+1], imageData[i+2]];
    if (containsObject(entry, unique_colors) == false) {
      unique_colors.push(entry)
    }
  }

  console.log(unique_colors);
}

function showTiles(img, scale) {
  tile_size = 8 * scale
  space = (1 * scale)
  for (var i = 0; i < img.width/tile_size; i++) {
    for (var j = 0; j < img.height/tile_size; j++) {
      tiles_ctx.drawImage(img, i*tile_size, j*tile_size, tile_size,
                          tile_size, i*(tile_size + space), j*(tile_size + space), tile_size, tile_size);
    }
  }
}

function showPalettes(img) {
  for (var i = 0; i < unique_colors.length; i++) {
    palettes_ctx.fillStyle = `rgba(${unique_colors[i][0]}, ${unique_colors[i][1]}, ${unique_colors[i][2]}, 1)`;
    var size = palettes_canvas.width/(unique_colors.length);
    palettes_ctx.fillRect((i * size),
                       0,
                       size,
                       size);
  }
}

function containsObject(obj, list) {
  var i;
  for (i = 0; i < list.length; i++) {
      if (list[i][0] === obj[0] &&
          list[i][1] === obj[1] &&
          list[i][2] === obj[2]) {
          return true;
      }
  }
  return false;
}