let path = ReactArt.Path.(make () |> moveTo x::0 y::0 |> lineTo x::10 y::10 |> close);

let transform = ReactArt.Transform.(make () |> scale x::2 y::2);

ReactDOMRe.renderToElementWithId <ReactArt.Surface width=500 height=500 /> "root";
