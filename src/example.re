let path = ReactArt.Path.(make () |> moveTo x::0 y::0 |> lineTo x::10 y::10 |> close);

let transform = ReactArt.Transform.(make () |> scale x::2 y::2);

module Demo = {
  type state =
    | Hovered
    | Idle;
  let component = ReasonReact.statefulComponent "Demo";
  let make _children => {
    ...component,
    initialState: fun () => Idle,
    render: fun {state, update} =>
      <ReactArt.Surface width=500 height=500>
        <ReactArt.Rectangle
          x=50
          y=50
          radius=10
          fill=(
            switch state {
            | Hovered =>
              LinearGradient (
                ReactArt.LinearGradient.make
                  stops::[("0.5", "#0f0"), ("1", "#00f")] x1::0 x2::100 y1::0 y2::200
              )
            | Idle => String "#f00"
            }
          )
          width=100
          height=200
          scale=(
            switch state {
            | Hovered => 1.2
            | Idle => 1.0
            }
          )
          onMouseOver=(update (fun _ _ => ReasonReact.Update Hovered))
          onMouseOut=(update (fun _ _ => ReasonReact.Update Idle))
        />
      </ReactArt.Surface>
  };
};

ReactDOMRe.renderToElementWithId <Demo /> "root";
