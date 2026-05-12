<script>
    const defaultSrc = "https://placehold.co/200x200/cccccc/333?text=Default";
    const defaultLog = "Hover or click the image";
    let imgSrc = $state(defaultSrc);
    let eventLog = $state(defaultLog);
</script>

<div
    class="p-8 bg-gray-50 min-h-auto text-black mt-5 rounded-xl flex flex-col items-center justify-center gap-4"
>
    <h2 class="text-xl font-semibold text-gray-800">
        Exercise 4: Image Mouse Events
    </h2>

    <button
        type="button"
        aria-label="Interactive image event target"
        onmouseover={() => {
            imgSrc = "https://placehold.co/200x200/3498db/fff?text=Mouse+Over";
            eventLog = "Event: mouseover";
        }}
        onmouseout={() => {
            imgSrc = "https://placehold.co/200x200/95a5a6/fff?text=Mouse+Out";
            eventLog = "Event: mouseout";
            setTimeout(() => {
                imgSrc = defaultSrc;
                eventLog = defaultLog;
            }, 3000);
        }}
        onmousedown={() => {
            imgSrc = "https://placehold.co/200x200/e74c3c/fff?text=Mouse+Down";
            eventLog = "Event: mousedown";
        }}
        onmouseup={() => {
            imgSrc = "https://placehold.co/200x200/2ecc71/fff?text=Mouse+Up";
            eventLog = "Event: mouseup";
        }}
        onblur={() => (imgSrc = defaultSrc)}
        onfocus={() => {}}
        class="rounded-xl transition-transform duration-150 hover:scale-105"
    >
        <img
            src={imgSrc}
            alt="Interactive"
            class="border-4 border-gray-300 rounded-xl cursor-pointer"
        />
    </button>

    <p class="text-sm italic text-gray-500">{eventLog}</p>
</div>
