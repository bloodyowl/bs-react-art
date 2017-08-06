# bs-react-art

> Reason bindings for ReactART

## Installation

```console
$ npm install --save bs-react-art
```

then `bs-react-art` to `bs-dependencies` in your `bsconfig.json`

## Usage

```reason
<ReactArt.Surface width=100 height=100>
  <ReactArt.Shape
    x=50
    y=300
    d=ReactArt.Path.(
        make ()
          |> moveTo x::0 y::50
          |> line x::10 y::10
          |> arc x::50 y::50 rx::10 ry::50 outer::10 counterClockwise::false rotation::300
          |> close
      )
    fill=(String "#c40")
  />
</ReactArt.Surface>
```

